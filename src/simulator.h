#include "env.h"
#include "Memory.h"
#include "Stage.h"
#include "Register.h"
#include "RegisterFile.h"

class Simulator {
public:
	Simulator();
	~Simulator();

	void start();
private:

	UINT32 pc;
	UINT32 sp;

	Memory* iMemory;
	Memory* dMemory;
	RegisterFile* reg;

	ITER cycle;
	bool halt;

	void loader();
	void simulate();
	void snapshotdump(ITER);
	void errordump(ITER);
};
