#include "Memory.h"

Memory* Memory::instructionInstance = NULL;
Memory* Memory::dataInstance = NULL;

Memory::Memory()
{
	body = new BYTE[MEMORY_SIZE];
	memset(body, 0, MEMORY_SIZE);
}

void Memory::set(UINT32 idx, BYTE val)
{
	this->body[idx] = val;
}

Memory* Memory::getInstructionMemory()
{
	if (instructionInstance == NULL) instructionInstance = new Memory();
	return instructionInstance;
}

Memory* Memory::getDataMemory()
{
	if (dataInstance == NULL) dataInstance = new Memory();
	return dataInstance;
}

// only combine the information (no endian), no need to sort
UINT32 Memory::getInstruction(UINT32 address)
{


	return body[address]  << 24 |
		body[address + 1] << 16 |
		body[address + 2] <<  8 |
		body[address + 3];
}

UINT32 Memory::getWord(UINT32 address)
{
	///if (address + 3 >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	return body[address] |
		body[address + 1] << 8 |
		body[address + 2] << 16 |
		body[address + 3] << 24;
}

UINT32 Memory::getHalfWord(UINT32 address)
{
	///if (address + 1 >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	return body[address] |
		body[address + 1] << 8;
}

UINT32 Memory::getByte(UINT32 address)
{
	///if (address >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	return body[address];
}

void Memory::saveWord(UINT32 address, UINT32 word)
{
	///if (address + 3 >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	body[address] = (word >> 0) & 0xff;
	body[address + 1] = (word >> 8) & 0xff;
	body[address + 2] = (word >> 16) & 0xff;
	body[address + 3] = (word >> 24) & 0xff;
}

void Memory::saveHalfWord(UINT32 address, UINT32 halfword)
{
	///if (address + 1 >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	body[address] = (halfword >> 0) & 0xff;
	body[address + 1] = (halfword >> 8) & 0xff;
}

void Memory::saveByte(UINT32 address, UINT32 byte)
{
	///if (address >= MEMORY_SIZE) throw ERR_MEMMORY_ADDRESS_OVERFLOW;
	body[address] = byte;
}
