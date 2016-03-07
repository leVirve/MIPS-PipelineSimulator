#ifndef __SATGE_H__
#define __SATGE_H__

#include "env.h"
#include "dedecode.h"
#define PC_PLUS4 0
#define PC_BRANCH 1
#define PC_JUMP 2

class Stage {

public:

	Stage() {};
	virtual bool execute() = 0;
    virtual char* check() = 0;
	enum StageId { WriteBack, MemoryAccess, Execute, Decode, Fetch };
	static Stage* GetStage(StageId id);

private:

	static Stage* StageWriteBack;
	static Stage* StageMemoryAccess;
	static Stage* StageExecute;
	static Stage* StageDecode;
	static Stage* StageFetch;

};


#endif
