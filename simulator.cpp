#include "simulator.h"

char *dat[5];
RegisterMap registers;
ErrorRegister err_registers;
FILE* snapshot = fopen(SNAPSHOT, "w");
FILE* err_dump = fopen(ERR_DUMP, "w");

Simulator::Simulator()
{
	pc = sp = 0;
	cycle = 0;
	halt = false;
	iMemory = Memory::getInstructionMemory();
	dMemory = Memory::getDataMemory();
	reg = RegisterFile::getInstance();
}

void Simulator::start()
{
	this->loader();
	this->simulate();
}

void Simulator::simulate()
{
	Stage* stages[STAGES] = {
		Stage::GetStage(Stage::WriteBack),
		Stage::GetStage(Stage::MemoryAccess),
		Stage::GetStage(Stage::Execute),
		Stage::GetStage(Stage::Decode),
		Stage::GetStage(Stage::Fetch)
	};
    RegisterFile* reg = RegisterFile::getInstance();
	while (!halt) {
	    /*for(ITER i = 0; i < 32; ++i)
            printf("$%02d: 0x%08X\n", i, reg->getRegister(i));
	    printf("PC: 0x%08X\n", registers["IF PC"]);*/
		// Five-Stages Pipeline
	    printf("\nCycle %d:\n", cycle);
		const char* StagesTag[5] = {"IF", "ID", "EX", "DM", "WB"};
		for(ITER i = 0; i < STAGES; ++i) {
		    dat[i]=stages[i]->check();
		}
		
		errordump(cycle);
        if (halt) break;
		snapshotdump(cycle);
		for(ITER i = 0; i < STAGES; ++i){
		    fprintf(snapshot, "%s: %s\n", StagesTag[i], dat[STAGES-i-1]);
		}
        fprintf(snapshot, "\n\n");
        cycle++;
		//snap
		for(ITER i = 0; i < STAGES; ++i) {

			halt = stages[i]->execute();
            if (halt) break;
		}
        if (halt) break;
		printf("halt %d\n", halt);
	}
}

void Simulator::loader()
{
	//PC = registers["PC"];

	FILE* instruction = fopen(INSTRUCTION_BIN, "r");
	FILE* data = fopen(DATA_BIN, "r");
	try {
		if (instruction == NULL) throw "No instruction binary file.";
		if (data == NULL) throw "No data binary file.";
		// Read in program_counter and stack_pointer
		fread(&pc, sizeof(UINT32), 1, instruction);
		fread(&sp, sizeof(UINT32), 1, data);
		// Set the infomation
		UINT32& ENTRY_POINT = pc;
		registers["IF PC"] = ENTRY_POINT;
		reg->setRegister(29, sp);
		// Read in the limitation
		UINT32 instruction_size, data_size;
		fread(&instruction_size, sizeof(UINT32), 1, instruction);
		fread(&data_size, sizeof(UINT32), 1, data);
		if(instruction_size >= MEMORY_SIZE) throw "Instruction Size Exceed Memory Size";
		if(data_size >= MEMORY_SIZE) throw "Data Size Exceed Memory Size";
		// Read into Memory
		BYTE tmp;
		for (ITER k = 0; k < 4 * instruction_size; ++k)
			fread(&tmp, sizeof(BYTE), 1, instruction),
			iMemory->set(ENTRY_POINT + k, tmp);
		for (ITER k = 0; k < 4 * data_size; ++k)
			fread(&tmp, sizeof(BYTE), 1, data),
			dMemory->set(k, tmp);

#ifdef _DEBUG
		printf("Instruction Size: %d\n", instruction_size);
		printf("Data Size: %d\n", data_size);
		printf("Initial PC = 0x%X\n", ENTRY_POINT);
#endif

	} catch (char* e) {
		fprintf(stderr, "%s\n", e);
	}

	fclose(instruction);
	fclose(data);
}
void Simulator::snapshotdump(ITER cycle)
{
	fprintf( snapshot, "cycle %d\n", cycle );
	for(ITER i = 0; i < 32; ++i) fprintf(snapshot, "$%02d: 0x%08X\n", i, reg->getRegister(i));
	fprintf(snapshot, "PC: 0x%08X\n", registers["IF PC"]);
}

void Simulator::errordump(ITER cycle)
{
	if(err_registers[ERR_WRITE_REG_ZERO]) fprintf( err_dump , "Write $0 error in cycle: %d\n", cycle);
	if(err_registers[ERR_D_MEM_ADDRESS_OVERFLOW]) fprintf( err_dump , "Address overflow in cycle: %d\n", cycle), halt = true;
	if(err_registers[ERR_D_MEM_MISALIGN]) fprintf( err_dump , "Misalignment error in cycle: %d\n", cycle), halt = true;
	if(err_registers[ERR_NUMBER_OVERFLOW]) fprintf( err_dump , "Number overflow in cycle: %d\n", cycle);
	if(err_registers[ERR_I_MEM_ADDRESS_OVERFLOW]) fprintf( err_dump , "Address overflow in cycle: %d\n", cycle), halt = true;
	if(err_registers[ERR_I_MEM_MISALIGN]) fprintf( err_dump , "Misalignment error in cycle: %d\n", cycle), halt = true;
	err_registers.clear();
}
