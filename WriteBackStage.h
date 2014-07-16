#ifndef __WRITEBACKSTAGE_H__
#define __WRITEBACKSTAGE_H__

#include "Stage.h"
#include "Register.h"
#include "RegisterFile.h"

class WriteBackStage : public Stage {

public:

	WriteBackStage();
	bool execute();
	char* check();
	char* state;

private:

	RegisterFile* reg;

	UINT32& _instruction;
	UINT32& instruction;
	UINT32& _pc;
	UINT32& _Op;
	UINT32& _WriteReg;
	UINT32& _ALUout;
	UINT32& _MDR;
	UINT32& _pcCarry;
	UINT32& _RegWrite;
    UINT32& _func;
	UINT32& pc;
	UINT32& Rt;
	UINT32& _Rt;
	UINT32& MDR;

};

#endif
