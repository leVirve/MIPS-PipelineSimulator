#ifndef __EXECUTESTAGE_H__
#define __EXECUTESTAGE_H__

#include "Stage.h"
#include "Register.h"
#include "RegisterFile.h"

class ExecuteStage : public Stage {

public:

	ExecuteStage();
	bool execute();
	void switcher();
	char* check();
	char* state;

	bool isOverflow(UINT32, UINT32);
	UINT32 twoComplement(UINT32);
	UINT32 BranchAdrr(UINT32);
	UINT32 JumpAddr(UINT32, UINT32);
	UINT32 SignExtImm(UINT32);

private:

	UINT32& _instruction;
	UINT32& instruction;
	UINT32& _pc;
	UINT32& _Op;
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
    RegisterFile* reg;
	UINT32& Op;
	UINT32& func;
    UINT32& func_;

	UINT32& shamt;
	UINT32& immediate;
	UINT32& address;
	UINT32& ReadData1;
	UINT32& ReadData2;

	UINT32& ALUout;
	UINT32& WriteReg;
	UINT32& WriteData;};

#endif
