#!/usr/bin/env python

import struct, sys
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from elftools.elf.sections import *
import lz4.block

R_AARCH64_ABS64	 = 257
R_AARCH64_ABS32	 = 258
R_AARCH64_ABS16	 = 259
R_AARCH64_PREL64 = 260
R_AARCH64_PREL32 = 261
R_AARCH64_PREL16 = 262

def main(input, output, format='nro'):
	format = format.lower()
	assert format in ('nro', 'nso')

	with file(input, 'rb') as f:
		elffile = ELFFile(f)
		elffile.iter_sections_by_type = lambda type: (x for x in elffile.iter_sections() if isinstance(x, type))

		symbols = {}
		symbolList = []
		for x in elffile.iter_sections_by_type(SymbolTableSection):
			for i, sym in enumerate(x.iter_symbols()):
				sectaddr = elffile.get_section(sym['st_shndx'])['sh_addr'] if isinstance(sym['st_shndx'], int) else 0
				symbols[sym.name] = sectaddr + sym['st_value']
				symbolList.append(sym.name)

		textCont, rodataCont, relaDynCont, dataCont, dynamicCont = [elffile.get_section_by_name(x).data() for x in ('.text', '.rodata', '.rela.dyn', '.data', '.dynamic')]
		csec = dict(text=textCont, rodata=rodataCont, relaDyn=relaDynCont, data=dataCont, dynamic=dynamicCont)

		def replace(tgt, offset, data):
			orig = csec[tgt]
			csec[tgt] = orig[:offset] + data + orig[offset+len(data):]

		for x in elffile.iter_sections_by_type(RelocationSection):
			tgtsect = elffile.get_section(x['sh_info'])
			tgt = tgtsect.name[1:]
			if tgt not in csec:
				continue
			for iter in x.iter_relocations():
				symname = symbolList[iter['r_info_sym']]
				if not symname.startswith('NORELOC_'):
					continue

				type = iter['r_info_type']
				if type == R_AARCH64_PREL32:
					replace(tgt, iter['r_offset'], struct.pack('<i', symbols[symname] + iter['r_addend'] - (tgtsect['sh_addr'] + iter['r_offset'])))
				elif type == R_AARCH64_ABS32:
					replace(tgt, iter['r_offset'], struct.pack('<I', symbols[symname] + iter['r_addend']))
				else:
					print 'Unknown relocation type!', type
					assert False

		text, rodata, data = csec['text'], csec['rodata'], csec['data']

                if len(rodata) & 0x7:
                        rodata += '\0' * (0x8 - (len(rodata) & 0x7))

                rodata += csec['relaDyn']

                if len(data) & 0x7:
                        data += '\0' * (0x8 - (len(data) & 0x7))

                data += csec['dynamic']
                
		if len(text) & 0xFFF:
			text += '\0' * (0x1000 - (len(text) & 0xFFF))
		if len(rodata) & 0xFFF:
			rodata += '\0' * (0x1000 - (len(rodata) & 0xFFF))
		if len(data) & 0xFFF:
			data += '\0' * (0x1000 - (len(data) & 0xFFF))

                bssSize = symbols['NORELOC_BSS_END_'] - symbols['NORELOC_BSS_START_']
                if bssSize & 0xFFF:
                        bssSize += 0x1000 - (bssSize & 0xFFF)
                
		if format == 'nro':
			#text = text[0x80:]
			with file(output, 'wb') as fp:
				fp.write(struct.pack('<IIII', 0, len(text) + len(rodata) + 8, 0, 0))
				fp.write('NRO0')
				fp.write(struct.pack('<III', 0, len(text) + len(rodata) + len(data), 0))
				fp.write(struct.pack('<IIII', 0, len(text), len(text), len(rodata)))
				fp.write(struct.pack('<IIII', len(text) + len(rodata), len(data), bssSize, 0))
				fp.write('\0' * 0x40)
				fp.write(text[0x80:])
				fp.write(rodata)
				fp.write(data)
		else:
			with file(output, 'wb') as fp:
				ctext, crodata, cdata = [lz4.block.compress(x, store_size=False) for x in (text, rodata, data)]

				fp.write('NSO0')
				fp.write('\0' * 0xC)

				off = 0x101
				fp.write(struct.pack('<IIII', off, 0, len(text), 0))
				off += len(ctext)
				fp.write(struct.pack('<IIII', off, len(text), len(rodata), 0))
				off += len(crodata)
				fp.write(struct.pack('<IIII', off, len(text) + len(rodata), len(data), symbols['NORELOC_BSS_END_'] - symbols['NORELOC_BSS_START_']))
				fp.write('\0' * 0x20)
				fp.write(struct.pack('<IIII', len(ctext), len(crodata), len(cdata), 0))
				fp.write('\0' * 0x91)
				
				fp.write(ctext)
				fp.write(crodata)
				fp.write(cdata)

if __name__=='__main__':
	sys.exit(main(*sys.argv[1:]))
