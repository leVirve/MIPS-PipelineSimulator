#ifndef __MEMORY__H__
#define __MEMORY__H__

#include "env.h"

class Memory {

private:

	// Block the Constructor
	Memory();
	// Singleton instance
	static Memory* instructionInstance;
	static Memory* dataInstance;
	// UINT32 sp;
	
public:

	static Memory* getInstructionMemory();
	static Memory* getDataMemory();

	UINT32 getInstruction(UINT32);
	void set(UINT32, BYTE);

	UINT32 getWord(UINT32);
	UINT32 getHalfWord(UINT32);
	UINT32 getByte(UINT32);
	void saveWord(UINT32, UINT32);
	void saveHalfWord(UINT32, UINT32);
	void saveByte(UINT32, UINT32);
private:
	
	BYTE* body;

};

#endif
