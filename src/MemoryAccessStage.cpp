#include "MemoryAccessStage.h"

MemoryAccessStage::MemoryAccessStage() :
	_instruction (registers["EXE instruction"]),
	instruction (registers["MEM instruction"]),
	_memory (Memory::getDataMemory()),
	_Op (registers["EXE Op"]),
	_pc (registers["EXE PC"]),
	_ALUout (registers["ALUout"]),
	_WriteData (registers["WriteData"]),
	_Rs (registers["EXE Rs"]),
	_Rd (registers["EXE Rd"]),
	_Rt (registers["EXE Rt"]),
	_WriteReg (registers["EXE WriteReg"]),
	_RegWrite (registers["EXE RegWrite"]),
	_pcCarry(registers["EXE PC Carry"]),
	RegWrite (registers["MEM RegWrite"]),
	pcCarry(registers["MEM PC Carry"]),
	pc (registers["MEM PC"]),
	Rs (registers["MEM Rs"]),
	Rt (registers["MEM Rt"]),
	Rd (registers["MEM Rd"]),
	Op (registers["MEM Op"]),
	_func (registers["EXE func"]),
	func (registers["MEM func"]),
	ALUout (registers["MEM ALUout"]),
	MDR (registers["MDR"]),
	WriteReg (registers["MEM WriteReg"]) {
}
char* MemoryAccessStage::check()
{
    return dedecode::de(_instruction);
}

bool MemoryAccessStage::execute()
{
	printf("\n--- MEM Stage ---\n");
	pc = _pc;
	Op = _Op;
	Rs = _Rs;
	Rt = _Rt;
	Rd = _Rd;
	func = _func;
    instruction = _instruction;
	RegWrite = _RegWrite;
	WriteReg = _WriteReg;
	printf("ALUout %d Data: %d\n", _ALUout, _WriteData);
	printf("ALUout %d Data: %d\n", ALUout, _WriteData);
	ALUout = _ALUout;
	printf("Opcode : %X\n", Op);
	switch (Op) {
	// load
	case 0x23:
		if (_ALUout % 4 == 0) {
			if (_ALUout < MEMORY_SIZE) MDR = _memory->getWord(_ALUout);
			printf("[addr %d] MDR %X\n", _ALUout, MDR);
		} else 
            err_registers[ERR_D_MEM_MISALIGN] = 1;
		if (_ALUout >/*=*/ MEMORY_SIZE - 4) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		puts("LW");
		break;
	case 0x21:
		if (_ALUout % 2 == 0) {
			if (_ALUout < MEMORY_SIZE) MDR = SignExtImm(_memory->getHalfWord(_ALUout));
			printf("[addr %d] MDR %X\n", _ALUout, MDR);
		} else err_registers[ERR_D_MEM_MISALIGN] = 1;
		if (_ALUout >/*=*/ MEMORY_SIZE - 2) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	case 0x25:
		if (_ALUout % 2 == 0) {
			if (_ALUout < MEMORY_SIZE) MDR = _memory->getHalfWord(_ALUout);
			printf("[addr %d] MDR %X\n", _ALUout, MDR);
		} else err_registers[ERR_D_MEM_MISALIGN] = 1;
		if (_ALUout >/*=*/ MEMORY_SIZE - 2) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	case 0x20:
		if (_ALUout < MEMORY_SIZE) {
			MDR = SignExtImmb(_memory->getByte(_ALUout));
			printf("[addr %d] MDR %X\n", _ALUout, MDR);
		}
		if (_ALUout >= MEMORY_SIZE) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	case 0x24:
		if (_ALUout < MEMORY_SIZE) {
			MDR = _memory->getByte(_ALUout);
			printf("[addr %d] MDR %X\n", _ALUout, MDR);
		}
		if (_ALUout >= MEMORY_SIZE) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	// save
	case 0x2B:
		if (_ALUout % 4 == 0) {
			if (_ALUout < MEMORY_SIZE) _memory->saveWord(_ALUout, _WriteData);
			printf("[addr %d] DATA %X\n", _ALUout, _WriteData);
		} else err_registers[ERR_D_MEM_MISALIGN] = 1;
		if (_ALUout >/*=?*/ MEMORY_SIZE - 4) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	case 0x29:
		if (_ALUout % 2 == 0) {
			if (_ALUout < MEMORY_SIZE) _memory->saveHalfWord(_ALUout, _WriteData);
			printf("[addr %d] DATA %X\n", _ALUout, _WriteData);
		} else err_registers[ERR_D_MEM_MISALIGN] = 1;
		if (_ALUout >/*=*/ MEMORY_SIZE - 2) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	case 0x28:
		if (_ALUout < MEMORY_SIZE) {
			_memory->saveByte(_ALUout, _WriteData);
			printf("[addr %d] DATA %X\n", _ALUout, _WriteData);
		}
		if (_ALUout >= MEMORY_SIZE) err_registers[ERR_D_MEM_ADDRESS_OVERFLOW] = 1;
		break;
	default: break;
	}

	printf("Rs: 0x%X, Rt: 0x%X, Rd: 0x%X\n", Rs, Rt, Rd);
	printf("RegWrite: %d\n", RegWrite);
    printf("Instruction: 0x%08x\n", instruction);
	return false;
}

UINT32 MemoryAccessStage::SignExtImm(UINT32 t)
{
	// {16{immediate[15]}, immediate}
	if ((t >> 15) == 0x0)
		return t & 0x0000ffff;
	else
		return t | 0xffff0000;
}

UINT32 MemoryAccessStage::SignExtImmb(UINT32 t)
{
	// {16{immediate[15]}, immediate}
	if ((t >> 7) == 0x0)
		return t & 0x000000ff;
	else
		return t | 0xffffff00;
}
