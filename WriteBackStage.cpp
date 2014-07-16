#include "WriteBackStage.h"

WriteBackStage::WriteBackStage() :
	_instruction (registers["MEM instruction"]),
	instruction (registers["WB instruction"]),
	_Op (registers["MEM Op"]),
	_pc (registers["MEM PC"]),
	_func (registers["MEM func"]),
	_WriteReg (registers["MEM WriteReg"]),
	_ALUout (registers["MEM ALUout"]),
	_MDR (registers["MDR"]),
	MDR (registers["WB MDR"]),
	_Rt (registers["MEM Rt"]),
	Rt (registers["WB Rt"]),
	_pcCarry(registers["MEM PC Carry"]),
	_RegWrite (registers["MEM RegWrite"]),
	pc (registers["WB PC"]) {
    state=NULL;
	reg = RegisterFile::getInstance();
}
char* WriteBackStage::check()
{
    return dedecode::de(_instruction);
}

bool WriteBackStage::execute()
{
	printf("\n--- WB Stage ---\n");
	printf("Opcode : %X\n", _Op);
	pc = _pc;
    instruction = _instruction;
    Rt = _Rt;printf("%X\n", _instruction);
    MDR = _MDR;
	switch (_Op) {
	case 0x00: // R-type
		if(_WriteReg != 0) reg->setRegister(_WriteReg, _ALUout);
		else if(instruction != 0x0 && _WriteReg == 0 && (instruction & 0x3F) != 0x08) err_registers[ERR_WRITE_REG_ZERO] = 1, printf("ERR_WRITE_REG_ZERO[R] : %X\n", _instruction);
		break;
	case 0x23: case 0x21: case 0x25: case 0x20: case 0x24: // load
		if(_WriteReg != 0) reg->setRegister(_WriteReg, _MDR);
		else if(_WriteReg == 0) err_registers[ERR_WRITE_REG_ZERO] = 1, printf("ERR_WRITE_REG_ZERO[load] : %X\n", _instruction);
		printf("[reg %d] MDR %X\n", _WriteReg, _MDR);
		break;
	case 0x08: case 0x0F: case 0x0C: case 0x0D: case 0x0E: // imm arithmetical calc
	case 0x0A:
		if(_WriteReg != 0) reg->setRegister(_WriteReg, _ALUout);
		else if(_WriteReg == 0) err_registers[ERR_WRITE_REG_ZERO] = 1, printf("ERR_WRITE_REG_ZERO[save] : %X\n", _instruction);
		printf("[reg %d] ALUout %X\n", _WriteReg, _ALUout);
		break;
	case 0x03: // jal
		reg->setRegister(31, _pc);//_pcCarry
		printf("[reg %d] PC Jump Carry %X\n", 31, _pc);
		break;
	case 0x3F: return true; break;
	}
	return false;
}
