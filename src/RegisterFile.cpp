#include "RegisterFile.h"

RegisterFile* RegisterFile::instance = NULL;

RegisterFile::RegisterFile()
{
	memset(body, 0, sizeof(body));
}

RegisterFile* RegisterFile::getInstance()
{
	if (instance == NULL) instance = new RegisterFile();
	return instance;
}

UINT32 RegisterFile::getRegister(int idx)
{
	if (idx < 0 || idx >= REGISTER_NUM) 
		throw "Register Access Overflow";

	return body[idx];
}

void RegisterFile::setRegister(int idx, UINT32 value)
{
	if (idx < 0 || idx >= REGISTER_NUM) 
		throw "Register Access Overflow";
	//'if (idx == 0) throw ERR_WRITE_REG_ZERO;

	body[idx] = value;
}