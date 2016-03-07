#ifndef __FETCHSTAGE_H__
#define __FETCHSTAGE_H__

#include "Stage.h"
#include "Memory.h"
#include "Register.h"

class FetchStage : public Stage {

public:

	FetchStage();
	bool execute();
	char* check();
	char* state;

private:

	Memory* memory;

	UINT32& _pc;
	UINT32& _PCSrcD;
	UINT32& _Flush;
	UINT32& _Stall;
	UINT32& _PCBranchD;
	UINT32& _PCJumpD;

	UINT32& instruction;
	UINT32& pc;

};

#endif
