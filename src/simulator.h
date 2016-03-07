#include "env.h"
#include "Memory.h"
#include "Stage.h"
#include "Register.h"
#include "RegisterFile.h"

class Simulator {
public:
    Simulator(int argc, const char** argv);
    ~Simulator();

    void start();
private:

    string instr_image;
    string data_image;

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
