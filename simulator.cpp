#include "simulator.h"

Simulator::Simulator()
{
	pc = 0;
	sp = 0;
}

void Simulator::loader()
{
	FILE* instruction = fopen(INSTRUCTION_BIN, "r");
	FILE* data = fopen(DATA_BIN, "r");
	try {
		if (instruction == NULL) throw "No instruction binary file.";
		if(data == NULL) throw "No data binary file.";
		fread(&pc, sizeof(UINT32), 1, instruction);
		fread(&sp, sizeof(UINT32), 1, data);
	} catch (char* e) {
		fprintf(stderr, "%s\n", e);
	}

	// memory->load(ir, data, ENTRY_POINT);
	// vcpu->setPC(ENTRY_POINT);
	// vcpu->setSP(STACK_POINT);
	// vcpu->setMemory(memory);
}

void Simulator::start()
{

}