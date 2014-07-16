#ifndef __DECODESTAGE_H__
#define __DECODESTAGE_H__

#include "Stage.h"
#include "Register.h"
#include "RegisterFile.h"
#include "ForwardUnit.h"

class DecodeStage : public Stage {

public:

	DecodeStage();
	bool execute();
	char* check();
	char* state;


private:

	UINT32 SignExtImm(UINT32);
	UINT32 BranchAdrr(UINT32);
	UINT32 JumpAddr(UINT32, UINT32);
	bool isOverflow(UINT32, UINT32);

	RegisterFile* reg;

	UINT32& _instruction;
	UINT32& instruction;
	UINT32& _pc;
	UINT32& PCSrcD;
	UINT32& Flush;
	UINT32& Stall;
	UINT32& PCBranchD;
	UINT32& PCJumpD;
	UINT32& RegWrite;
	UINT32& pc;
	UINT32& Op;
	UINT32& func;
	UINT32& pcCarry;

	UINT32& Rs;
	UINT32& Rt;
	UINT32& Rd;
	UINT32& shamt;
	UINT32& immediate;
	UINT32& address;
	UINT32& ReadData1;
	UINT32& ReadData2;

	UINT32 PCtemp;
	UINT32 iOp;
	UINT32 ifunc;
    UINT32 iRs;
	UINT32 iRt;
	UINT32 iRd;
	UINT32 ishamt;
	UINT32 iimmediate;
	UINT32 iaddress;
	UINT32 iRegWrite;
};

#endif
