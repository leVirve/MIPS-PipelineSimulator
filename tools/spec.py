from collections import defaultdict
from decoder import R_decoder, I_decoder, J_decoder, Halt_decoder


decoders = defaultdict(lambda: I_decoder)
decoders[0x0] = R_decoder
decoders[0x2] = J_decoder
decoders[0x3] = J_decoder
decoders[0x3f] = Halt_decoder


def decode(instruction):
    opcode = instruction >> 26 & 0x3f
    decoder = decoders[opcode]
    return decoder(instruction)
