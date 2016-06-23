
opcode_map = {
    0x3F: 'HALT',
    0x03: 'JAL',
    0x02: 'J',
    0x05: 'BNE',
    0x04: 'BEQ',
    0x0A: 'SLTI',
    0x0E: 'NORI',
    0x0D: 'ORI',
    0x0C: 'ANDI',
    0x0F: 'LUI',
    0x28: 'SB',
    0x29: 'SH',
    0x2B: 'SW',
    0x24: 'LBU',
    0x20: 'LB',
    0x25: 'LHU',
    0x21: 'LH',
    0x23: 'LW',
    0x08: 'ADDI',
    0x00: {
        0x20: 'ADD',
        0x22: 'SUB',
        0x24: 'AND',
        0x25: 'OR',
        0x26: 'XOR',
        0x27: 'NOR',
        0x28: 'NAND',
        0x2A: 'SLT',
        0x02: 'SRL',
        0x03: 'SRA',
        0x08: 'JR',
        0x00: 'SLL',
    }
}


def R_decoder(instruction):
    data = {
        'opcode': instruction >> 26 & 0x3f,
        'rs': instruction >> 21 & 0x1f,
        'rt': instruction >> 16 & 0x1f,
        'rd': instruction >> 11 & 0x1f,
        'shamt': instruction >> 6 & 0x1f,
        'func': instruction & 0x3f,
    }
    data['info'] = {'opname': opcode_map[data['opcode']][data['func']]}
    return data


def I_decoder(instruction):
    data = {
        'opcode': instruction >> 26 & 0x3f,
        'rs': instruction >> 21 & 0x1f,
        'rt': instruction >> 16 & 0x1f,
        'immediate': instruction & 0xffff,
    }
    data['info'] = {'opname': opcode_map[data['opcode']]}
    return data


def J_decoder(instruction):
    data = {
        'opcode': instruction >> 26 & 0x3f,
        'address': instruction & 0x3ffffff,
    }
    data['info'] = {'opname': opcode_map[data['opcode']]}
    return data


def Halt_decoder(instruction):
    data = {'opcode': instruction >> 26 & 0x3f}
    data['info'] = {'opname': opcode_map[data['opcode']]}
    return data
