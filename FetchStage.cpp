#include "FetchStage.h"
#include <cstring>
UINT32 _instruction;
FetchStage::FetchStage() :
	memory (Memory::getInstructionMemory()),
	_pc (registers["PC"]),
	_PCSrcD (registers["PCSrc"]),
	_PCBranchD (registers["PCBranchD"]),
	_PCJumpD (registers["PCJumpD"]),
	_Flush (registers["Flush"]),
	_Stall (registers["Stall"]),
	instruction (registers["instruction"]),
	pc (registers["IF PC"]) {
}
char* FetchStage::check()
{
    UINT32 raw = memory->getInstruction(pc);
	_instruction =
		(raw >> 24) & 0xff |
		(raw >> 8) & 0xff00 |
		(raw << 8) & 0xff0000 |
		(raw << 24) & 0xff000000;

	// Write into IF/ID registers

    char* inp = new char[1000];
    sprintf(inp, "0x%08X", _instruction);

    if(_Stall){
        strcat(inp, " to_be_stalled");
    } else if(_Flush) {
        strcat(inp, " to_be_flushed");
	}
    return inp;
}

bool FetchStage::execute()
{

	if(!_Stall)instruction = _instruction;
	printf("\n--- IF Stage ---\n");
	printf("PC: 0x%08x\n PCSrc =  %d (_Stall: %d, _Flush: %d)\n", pc, _PCSrcD, _Stall, _Flush);
	//UINT32 raw = memory->getInstruction(pc);
	if (_pc >= MEMORY_SIZE) err_registers[ERR_I_MEM_ADDRESS_OVERFLOW] = 1;
	if (_pc % 4 != 0) err_registers[ERR_I_MEM_MISALIGN] = 1;
    if(_Stall){
    } else if(_Flush) {
        instruction = 0x0;
		switch (_PCSrcD) {
		//case PC_PLUS4: pc = _pc; break;// TEST NOT SURE
		case PC_BRANCH: pc = _PCBranchD; break;
		case PC_JUMP: pc = _PCJumpD; break;
		}
    } else {
        UINT32 nextPC = pc + 4;
        switch (_PCSrcD) {
        case PC_PLUS4: pc = nextPC; break;
        case PC_BRANCH: pc = _PCBranchD; break;
        case PC_JUMP: pc = _PCJumpD; break;
        }
    }
	/*
	UINT32 _instruction =
		(raw >> 24) & 0xff |
		(raw >> 8) & 0xff00 |
		(raw << 8) & 0xff0000 |
		(raw << 24) & 0xff000000;

	// Write into IF/ID registers
	instruction = _instruction;*/

	printf("PC: 0x%08x\n", pc);
	printf("Instruction: 0x%08x\n", instruction);
	return false;
}
