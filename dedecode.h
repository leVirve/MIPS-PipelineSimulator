#ifndef __DECODE_H__
#define __DECODE_H__

class dedecode{

public:

    static char* de(UINT32 ins){
    if(ins==0x0) return (char*)"NOP";
    switch((ins >> 26) & 0x3F){
    case 0x3F: return (char*)"HALT";
    case 0x03: return (char*)"JAL";
    case 0x02: return (char*)"J";
    case 0x05: return (char*)"BNE";
    case 0x04: return (char*)"BEQ";
    case 0x0A: return (char*)"SLTI";
    case 0x0E: return (char*)"NORI";
    case 0x0D: return (char*)"ORI";
    case 0x0C: return (char*)"ANDI";
    case 0x0F: return (char*)"LUI";
    case 0x28: return (char*)"SB";
    case 0x29: return (char*)"SH";
    case 0x2B: return (char*)"SW";
    case 0x24: return (char*)"LBU";
    case 0x20: return (char*)"LB";
    case 0x25: return (char*)"LHU";
    case 0x21: return (char*)"LH";
    case 0x23: return (char*)"LW";
    case 0x08: return (char*)"ADDI";
    case 0x00: switch(0x0000003F & ins){
        case 0x20: return (char*)"ADD";
        case 0x22: return (char*)"SUB";
        case 0x24: return (char*)"AND";
        case 0x25: return (char*)"OR";
        case 0x26: return (char*)"XOR";
        case 0x27: return (char*)"NOR";
        case 0x28: return (char*)"NAND";
        case 0x2A: return (char*)"SLT";
        case 0x02: return (char*)"SRL";
        case 0x03: return (char*)"SRA";
        case 0x08: return (char*)"JR";
        case 0x00: return (char*)"SLL";
        }
	default: return NULL;
    }
}


};

#endif
