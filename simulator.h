#include "env.h"
#include "CPU.h"
#include "Memory.h"

class Simulator {
public:
	Simulator();
	~Simulator();
	
	void start();
	void test() { return; }
private:

	// Program Counter
	UINT32 pc;

	// Stack Pointer
	UINT32 sp;

	CPU* cpu;

	Memory* memory;

	void loader();
};