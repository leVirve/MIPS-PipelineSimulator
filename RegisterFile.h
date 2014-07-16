#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include "env.h"

#define REGISTER_NUM 32

class RegisterFile {

private:
	
	// Block the Constructor
	RegisterFile();
	// Singleton instance
	static RegisterFile* instance;

	UINT32 body[REGISTER_NUM];

public:

	static RegisterFile* getInstance();
	
	UINT32 getRegister(int);
	void setRegister(int, UINT32);

};

#endif