#!/usr/bin/env python

import struct, sys, hashlib
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from elftools.elf.sections import *
from itertools import *
import lz4.block

R_AARCH64_ABS64 = 257
R_AARCH64_ABS32 = 258
R_AARCH64_ABS16 = 259
R_AARCH64_PREL64 = 260
R_AARCH64_PREL32 = 261
R_AARCH64_PREL16 = 262


def main(input, output, format='nro'):
	format = format.lower()
	assert format in ('nro', 'nso')

	with open(input, 'rb') as f:
		elffile = ELFFile(f)

		load_segments = list(filter(lambda x: x['p_type'] == 'PT_LOAD', elffile.iter_segments()))
		
		assert len(load_segments) == 4

		code_segment = load_segments[0]
		rodata_segment = load_segments[1]
		data_segment = load_segments[2]
		bss_segment = load_segments[3]

		assert code_segment['p_vaddr'] & 0xFFF == 0
		assert code_segment['p_flags'] == 5
		
		assert rodata_segment['p_vaddr'] & 0xFFF == 0
		assert rodata_segment['p_flags'] == 4
		
		assert data_segment['p_vaddr'] & 0xFFF == 0
		assert data_segment['p_flags'] == 6
		
		assert bss_segment['p_vaddr'] & 0xFFF == 0
		assert bss_segment['p_filesz'] == 0
		assert bss_segment['p_flags'] == 6

		def page_pad(data):
			return data + ('\0'.encode() * (((len(data) + 0xFFF) & ~0xFFF) - len(data)))
		
		code = page_pad(code_segment.data())
		rodata = page_pad(rodata_segment.data())
		data = page_pad(data_segment.data())
		
		if format == 'nro':
			# text = text[0x80:]
			with open(output, 'wb') as fp:
				dot = 0
				
				fp.write(code[:0x10]) # first branch instruction, mod0 offset, and padding
				
				# NRO header
				fp.write('NRO0'.encode())
				fp.write(struct.pack('<III', 0, len(code) + len(rodata) + len(data), 0))
				
				assert dot & 0xFFF == 0
				assert code_segment['p_vaddr'] == dot
				fp.write(struct.pack('<II', dot, len(code))) # exec segment
				dot+= len(code)
				
				assert dot & 0xFFF == 0
				assert rodata_segment['p_vaddr'] == dot
				fp.write(struct.pack('<II', dot, len(rodata))) # read only segment
				dot+= len(rodata)
				
				assert dot & 0xFFF == 0
				assert data_segment['p_vaddr'] == dot
				fp.write(struct.pack('<II', dot, len(data))) # rw segment
				dot+= len(data)

				assert dot & 0xFFF == 0
				assert bss_segment['p_vaddr'] == dot
				fp.write(struct.pack('<II', (bss_segment['p_memsz'] + 0xFFF) & ~0xFFF, 0))
				
				fp.write('\0'.encode() * 0x40)
				
				fp.write(code[0x80:])
				fp.write(rodata)
				fp.write(data)
		else:
			with open(output, 'wb') as fp:
				ccode, crodata, cdata = [lz4.block.compress(x, store_size=False) for x in (code, rodata, data)]

				fp.write('NSO0'.encode())
				fp.write(struct.pack('<III', 0, 0, 0x3f))

				off = 0x100
				dot = 0

				assert dot & 0xFFF == 0
				assert code_segment['p_vaddr'] == dot
				fp.write(struct.pack('<IIII', off, dot, len(code), 0))
				off += len(ccode)
				dot += len(code)

				assert dot & 0xFFF == 0
				assert rodata_segment['p_vaddr'] == dot
				fp.write(struct.pack('<IIII', off, dot, len(rodata), 0))
				off += len(crodata)
				dot += len(rodata)

				assert dot & 0xFFF == 0
				assert data_segment['p_vaddr'] == dot
				fp.write(struct.pack('<IIII', off, dot, len(data), (bss_segment['p_memsz'] + 0xFFF) & ~0xFFF))
				off += len(cdata)
				dot += len(data)

				assert bss_segment['p_vaddr'] == dot

				fp.write('\0'.encode() * 0x20)
				
				fp.write(struct.pack('<IIII', len(ccode), len(crodata), len(cdata), 0))
				
				fp.write('\0'.encode() * 0x30)

				for x in (code, rodata, data):
					 m = hashlib.sha256()
					 m.update(x)
					 assert m.digest_size == 0x20
					 fp.write(m.digest())

				fp.write(ccode)
				fp.write(crodata)
				fp.write(cdata)


if __name__ == '__main__':
	sys.exit(main(*sys.argv[1:]))
