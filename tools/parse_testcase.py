import struct

from spec import decode

filename = '../testcase/%s/iimage.bin' % 'archi10'

struct_fmt = '=I'
struct_len = struct.calcsize(struct_fmt)
struct_unpack = struct.Struct(struct_fmt).unpack_from


def unpack(f):
    return struct_unpack(f.read(struct_len))[0]

instructions = []
with open(filename, 'rb') as f:
    pc, sz = unpack(f), unpack(f)
    print(pc, sz)
    instructions = [unpack(f) for _ in range(sz)]

for instruction in instructions:
    r = decode(instruction)
    opname = r['info']['opname']
    del r['info'], r['opcode']
    if 'func' in r:
        del r['func']
    print(opname, r)
