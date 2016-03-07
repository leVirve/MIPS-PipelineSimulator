#ifndef __MEMORY_ACCESS_STAGE_H__
#define __MEMORY_ACCESS_STAGE_H__

#include "Stage.h"
#include "Register.h"
#include "Memory.h"

class MemoryAccessStage : public Stage {

public:

	MemoryAccessStage();
	bool execute();
	char* check();
	char* state;

private:

	Memory* _memory;
	UINT32 SignExtImm(UINT32);
	UINT32 SignExtImmb(UINT32);

	UINT32& _instruction;
	UINT32& instruction;
	UINT32& _Op;
	UINT32& _ALUout;
	UINT32& _WriteReg;
	UINT32& _WriteData;

	UINT32& _pc;
	UINT32& _Rs;
	UINT32& _Rt;
	UINT32& _Rd;
	UINT32& _pcCarry;
	UINT32& _RegWrite;
	UINT32& pcCarry;
	UINT32& RegWrite;
	UINT32& pc;
	UINT32& Rs;
	UINT32& Rt;
	UINT32& Rd;
	UINT32& func;
    UINT32& _func;

	UINT32& Op;
	UINT32& MDR;
	UINT32& WriteReg;
	UINT32& ALUout;

};

#endif
