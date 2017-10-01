import sys
sys.path.append('SwIPC')
import idparser

import glob, re

def emitInt(x):
	return '0x%x' % x if x > 9 else str(x)

typemap = dict(
	i8='int8_t', 
	i16='int16_t', 
	i32='int32_t', 
	i64='int64_t', 
	i128='int128_t', 
	u8='uint8_t', 
	u16='uint16_t', 
	u32='uint32_t', 
	u64='uint64_t', 
	u128='uint128_t', 
	f32='float32_t', 
	pid='gpid', 
	bool='bool', 
)

typesizes = dict(
	i8=1, 
	i16=2, 
	i32=4, 
	i64=8, 
	i128=16, 
	u8=1, 
	u16=2, 
	u32=4, 
	u64=8, 
	u128=16, 
	f32=4, 
	pid=8, 
	bool=1, 
)

allTypes = None

def typeSize(type):
	if type[0] in ('unknown', 'i8', 'u8'):
		return 1
	elif type[0] == 'bytes':
		return type[1]
	elif type[0] in allTypes:
		return typeSize(allTypes[type[0]])
	elif type[0] in typesizes:
		return typesizes[type[0]]
	return 1

def splitByNs(obj):
	ons = {}
	for type, x in obj.items():
		ns = type.rsplit('::', 1)[0] if '::' in type else None
		name = type.rsplit('::', 1)[-1]
		if ns not in ons:
			ons[ns] = {}
		ons[ns][name] = x
	return ons

def retype(spec, noIndex=False):
	if spec[0] == 'unknown':
		return 'uint8_t'
	elif spec[0] == 'bytes':
		return 'uint8_t%s' % ('[%s]' % emitInt(spec[1]) if not noIndex else ' *')
	else:
		return typemap[spec[0]] if spec[0] in typemap else spec[0];

def formatParam(param, input, i):
	name, spec = param
	if name is None:
		name = '_%i' % i

	hasSize = False

	if spec[0] == 'align':
		return formatParam((name, spec[2]), input, i)

	if spec[0] == 'bytes':
		type = 'uint8_t *'
	elif spec[0] == 'unknown':
		assert False
	elif spec[0] == 'buffer':
		type = '%s *' % retype(spec[1])
		hasSize = True
	elif spec[0] == 'array':
		type = retype(spec[1]) + ' *'
		hasSize = True
	elif spec[0] == 'object':
		type = '%s *' % spec[1][0]
	elif spec[0] == 'KObject':
		type = 'KObject *'
	else:
		type = typemap[spec[0]] if spec[0] in typemap else spec[0]

	if type.endswith(']'):
		arrspec = type[type.index('['):]
		type = type[:-len(arrspec)]
	else:
		arrspec = ''

	return '%s %s%s %s%s%s' % ('IN' if input else 'OUT', type, '&' if not input and (not type.endswith('*') and not arrspec) else '', name, arrspec, ', guint %s_size' % name if hasSize else '')

def generatePrototype(func):
	return ', '.join([formatParam(x, True, i) for i, x in enumerate(func['inputs'])] + [formatParam(x, False, i + len(func['inputs'])) for i, x in enumerate(func['outputs'])])

def isPointerType(type):
	if type[0] in typesizes:
		return False
	elif type[0] == 'bytes':
		return True
	elif type[0] in allTypes:
		return isPointerType(allTypes[type[0]])
	return True

AFTER = 'AFTER'

def generateCaller(qname, fname, func):
	def tempname():
		tempI[0] += 1
		return 'temp%i' % tempI[0]
	params = []
	logFmt, logElems = [], []
	tempI = [0]
	inpOffset = 8
	bufOffs = {}
	hndOff = 0
	objOff = 0
	bufSizes = 0
	for name, elem in func['inputs']:
		type, rest = elem[0], elem[1:]
		if type in ('array', 'buffer'):
			if rest[1] not in bufOffs:
				bufOffs[rest[1]] = 0
			cbo = bufOffs[rest[1]]
			bufOffs[rest[1]] += 1
			an, sn, bn = tempname(), tempname(), tempname()
			yield 'guint %s;' % sn
			yield 'auto %s = req.getBuffer(%s, %i, %s);' % (an, emitInt(rest[1]), cbo, sn)
			#yield 'auto %s = new uint8_t[%s];' % (bn, sn)
			yield 'ctu->cpu.readmem(%s, %s, %s);' % (an, bn, sn)
			params.append('(%s *) %s' % (retype(rest[0]), bn))
			params.append(sn)
			logFmt.append('%s *%s= buffer<0x" ADDRFMT ">' % (retype(rest[0]), '%s ' % name if name else ''))
			logElems.append(sn)
			bufSizes += 1
			yield AFTER, 'delete[] %s;' % bn
		elif type == 'object':
			params.append('ctu->getHandle<%s>(req.getMoved(%i))' % (rest[0][0], objOff))
			logFmt.append('%s %s= 0x%%x' % (rest[0][0], '%s ' % name if name else ''))
			logElems.append('req.getMoved(%i)' % objOff)
			objOff += 1
		elif type == 'KObject':
			params.append('ctu->getHandle<KObject>(req.getCopied(%i))' % hndOff)
			logFmt.append('KObject %s= 0x%%x' % ('%s ' % name if name else ''))
			logElems.append('req.getCopied(%i)' % objOff)
			hndOff += 1
		elif type == 'pid':
			params.append('req.pid')
		else:
			if elem[0] == 'align':
				alignment = elem[1]
				elem = elem[2]
			else:
				alignment = min(8, typeSize(elem))
			while inpOffset % alignment:
				inpOffset += 1
			if isPointerType(elem):
				params.append('req.getDataPointer<%s>(%s)' % (retype(elem, noIndex=True), emitInt(inpOffset)))
				logFmt.append('%s %s= %%s' % (retype(elem), '%s ' % name if name else ''))
				logElems.append('bufferToString(req.getDataPointer<uint8_t *>(%s), %s).c_str()' % (emitInt(inpOffset), emitInt(typeSize(elem))))
			else:
				params.append('req.getData<%s>(%s)' % (retype(elem), emitInt(inpOffset)))
				if typeSize(elem) == 16:
					logFmt.append('%s %s= %%s' % (retype(elem), '%s ' % name if name else ''))
					logElems.append('bufferToString(req.getDataPointer<uint8_t *>(%s), %s).c_str()' % (emitInt(inpOffset), emitInt(typeSize(elem))))
				else:
					type = retype(elem)
					ct = '0x%x'
					if type == 'float32_t':
						ct = '%f'
					elif typeSize(elem) == 8:
						ct = '0x" ADDRFMT "'
					logFmt.append('%s %s= %s' % (type, '%s ' % name if name else '', ct))
					logElems.append('%sreq.getData<%s>(%s)' % ('(double) ' if type == 'float32_t' else '', type, emitInt(inpOffset)))
			inpOffset += typeSize(elem)

	outOffset = 8
	hndOff = 0
	objOff = 0
	for i, (name, elem) in enumerate(func['outputs']):
		if name is None:
			name = '_%i' % (i + len(func['inputs']))
		type, rest = elem[0], elem[1:]
		if type in ('array', 'buffer'):
			if rest[1] not in bufOffs:
				bufOffs[rest[1]] = 0
			cbo = bufOffs[rest[1]]
			bufOffs[rest[1]] += 1
			an, sn, bn = tempname(), tempname(), tempname()
			yield 'guint %s;' % sn
			yield 'auto %s = req.getBuffer(%s, %i, %s);' % (an, emitInt(rest[1]), cbo, sn)
			#yield 'auto %s = new uint8_t[%s];' % (bn, sn)
			bufSizes += 1
			yield AFTER, 'ctu->cpu.writemem(%s, %s, %s);' % (an, bn, sn)
			yield AFTER, 'delete[] %s;' % bn
		elif type == 'object':
			yield AFTER, '%s = new %s(resp.move_handles[%i]);' % (name, rest[0][0], objOff)
			objOff += 1
		elif type == 'KObject':
			hndOff += 1
		elif type == 'pid':
			assert False
		else:
			if elem[0] == 'align':
				alignment = elem[1]
				elem = elem[2]
			else:
				alignment = min(8, typeSize(elem))
			while outOffset % alignment:
				outOffset += 1
			if isPointerType(elem):
				tn = tempname()
				yield 'auto %s = resp.getDataPointer<%s>(%s);' % (tn, retype(elem, noIndex=True), emitInt(outOffset))
				params.append(tn)
			else:
				params.append('*resp.getDataPointer<%s *>(%s)' % (retype(elem), emitInt(outOffset)))
			outOffset += typeSize(elem)

	yield 'auto ret = ipc_send(session, &req, &resp);'
	yield AFTER
	yield 'return ret;'

def reorder(gen):
	after = []
	for x in gen:
		if x == AFTER:
			for elem in after:
				yield elem
		elif isinstance(x, tuple) and x[0] == AFTER:
			after.append(x[1])
		else:
			yield x

def parsePartials(code):
	code = '\n'.join(re.findall(r'/\*\$IPC\$(.*?)\*/', code, re.M|re.S))
	return partialparser.parse(code)

def main():
	global allTypes

	types, ifaces, services = idparser.getAll()

	allTypes = types

	typesByNs = splitByNs(types)
	ifacesByNs = splitByNs(ifaces)

	namespaces = {x : [] for x in typesByNs.keys() + ifacesByNs.keys()}

	for ns, types in typesByNs.items():
		for name, spec in sorted(types.items(), key=lambda x: x[0]):
			retyped, plain = retype(spec, noIndex=True), retype(spec)
			namespaces[ns].append('using %s = %s;%s' % (name, retyped, ' // ' + plain if retyped != plain else ''))

	for ns, ifaces in ifacesByNs.items():
		for name in sorted(ifaces.keys()):
			namespaces[ns].append('class %s;' % name)

	with file('lib/ipcClients.h', 'w') as fp:
		print >>fp, '#pragma once'
		print >>fp, '#include<libtransistor/ipc.h>'
		print >>fp

		for ns, elems in sorted(namespaces.items(), key=lambda x: x[0]):
			if ns is not None:
				print >>fp, 'namespace %s {' % ns
			hasUsing = False
			for elem in elems:
				if not hasUsing and elem.startswith('using'):
					hasUsing = True
				elif hasUsing and elem.startswith('class'):
					print >>fp
					hasUsing = False
				print >>fp, ('\t' if ns is not None else '') + elem
			if ns is not None:
				print >>fp, '}'

		print >>fp

		for ns, ifaces in sorted(ifacesByNs.items(), key=lambda x: x[0]):
			print >>fp, '%snamespace %s {' % ('//// ' if ns is None else '', ns)
			for name, funcs in sorted(ifaces.items(), key=lambda x: x[0]):
				qname = '%s::%s' % (ns, name) if ns else name
				print >>fp, '\tclass %s {' % name
				print >>fp, '\tpublic:'
				print >>fp, '\t\t%s();' % name
				for fname, func in sorted(funcs.items(), key=lambda x: x[0]):
					print >>fp, '\t\tuint32_t %s(%s);' % (fname, generatePrototype(func))
				print >>fp, '\t};'
			print >>fp, '%s}' % ('//// ' if ns is None else '')

			print >>fp, '#ifdef DEFINE_CALLERS'
			for name, funcs in sorted(ifaces.items(), key=lambda x: x[0]):
				qname = '%s::%s' % (ns, name) if ns else name
				for fname, func in sorted(funcs.items(), key=lambda x: x[0]):
					print >>fp, 'uint32_t %s::%s(%s) {' % (qname, fname, generatePrototype(func))
					print >>fp, '\tipc_request_t req;'
					print >>fp, '\tipc_response_t resp;'
					print >>fp, '\tmemset(&req, 0, sizeof(ipc_request_t));'
					print >>fp, '\n'.join('\t' + x for x in reorder(generateCaller(qname, fname, func)))
					print >>fp, '}'
			print >>fp, '#endif // DEFINE_CALLERS'

if __name__=='__main__':
	main(*sys.argv[1:])
