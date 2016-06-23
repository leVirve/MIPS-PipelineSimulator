#include "ExecuteStage.h"

ExecuteStage::ExecuteStage() :
	_instruction (registers["ID instruction"]),
	instruction (registers["EXE instruction"]),
	_pc (registers["ID PC"]),
	_Op (registers["ID Op"]),
	_Rs (registers["ID Rs"]),
	_Rt (registers["ID Rt"]),
	_Rd (registers["ID Rd"]),
	_pcCarry (registers["ID PC Carry"]),
	_RegWrite (registers["ID RegWrite"]),
	pcCarry (registers["EXE PC Carry"]),
	RegWrite (registers["EXE RegWrite"]),
	pc (registers["EXE PC"]),
	Rs (registers["EXE Rs"]),
	Rt (registers["EXE Rt"]),
	Rd (registers["EXE Rd"]),
	Op (registers["EXE Op"]),
	func (registers["ID func"]),
	func_ (registers["EXE func"]),
	shamt (registers["ID shamt"]),
	immediate (registers["ID immediate"]),
	address (registers["ID address"]),
	ReadData1 (registers["ReadData1"]),
	ReadData2 (registers["ReadData2"]),
	ALUout (registers["ALUout"]),
	WriteReg (registers["EXE WriteReg"]),
	WriteData (registers["WriteData"]) {
    this->reg = RegisterFile::getInstance();
}

unsigned int exe_readdata1 = 0, exe_readdata2 = 0;

char* ExecuteStage::check()
{
	char* inp = new char[1000];
	char* ip = new char[20];
	sprintf(inp, "%s", dedecode::de(_instruction));
    if (registers["EXE RegWrite"] == 1 && registers["EXE Rd"] != 0 && registers["EXE Rd"] == _Rs
        && !(_Op == 0 && (func == SLL || func == SRL || func == SRA))
        && _Op != LUI)
        sprintf(ip, " fwd_EX-DM_rs_$%d", _Rs), strcat(inp, ip), ReadData1 = exe_readdata1 = registers["ALUout"];
    else if (registers["EXE RegWrite"] == 2 && registers["EXE Rt"] != 0 && registers["EXE Rt"] == _Rs
        && !(_Op == 0 && (func == SLL || func == SRL || func == SRA))
        && _Op != LUI)
        sprintf(ip, " fwd_EX-DM_rs_$%d", _Rs), strcat(inp, ip), ReadData1 = exe_readdata1 = registers["ALUout"];
    else if (
        (_Op != 0x05 && _Op != 0x04 && _Op != 0x02 && _Op != 0x03 && _Op != LUI)
        && registers["MEM RegWrite"] == 1
        && registers["MEM Rd"] != 0
        && registers["MEM Rd"] == _Rs
        && !(_Op == 0 && (func == SLL || func == SRL || func == SRA)))
        sprintf(ip, " fwd_DM-WB_rs_$%d", _Rs), strcat(inp, ip), ReadData1 = exe_readdata1 = registers["MEM ALUout"];
    else if (
        (_Op != 0x05 && _Op != 0x04 && _Op != 0x02 && _Op != 0x03 && _Op != LUI)
        && registers["MEM RegWrite"] == 2
        && registers["MEM Rt"] != 0
        && registers["MEM Rt"] == _Rs
        && !(_Op == 0 && (func == SLL || func == SRL || func == SRA)))
        sprintf(ip, " fwd_DM-WB_rs_$%d", _Rs), strcat(inp, ip), ReadData1 = exe_readdata1 = registers["MEM ALUout"];
    else if (registers["MEM RegWrite"] == 3 && registers["MEM Rt"] != 0 && registers["MEM Rt"] == _Rs
        && !(_Op == 0 && (func == SLL || func == SRL || func == SRA))
        && _Op != LUI)
        sprintf(ip, " fwd_DM-WB_rs_$%d", _Rs), strcat(inp, ip), ReadData1 = exe_readdata1 = registers["MDR"];
    else
		exe_readdata1 = reg->getRegister(_Rs);
	if ((_RegWrite==1||_RegWrite==4) && registers["EXE RegWrite"] == 1 && registers["EXE Rd"] != 0 && registers["EXE Rd"] == _Rt)
		sprintf(ip, " fwd_EX-DM_rt_$%d", _Rt), strcat(inp, ip), ReadData2 = exe_readdata2 = registers["ALUout"];
	else if ((_RegWrite==1||_RegWrite==4) && registers["EXE RegWrite"] == 2 && registers["EXE Rt"] != 0 && registers["EXE Rt"] == _Rt)
		sprintf(ip, " fwd_EX-DM_rt_$%d", _Rt), strcat(inp, ip), ReadData2 = exe_readdata2 = registers["ALUout"];
	else if ((_RegWrite==1||_RegWrite==4) && (_Op != 0x05 && _Op != 0x04 && _Op != 0x02 && _Op != 0x03 && !(func == 0x08 && _Op == 0x0)) && registers["MEM RegWrite"] == 1 && registers["MEM Rd"] != 0 && registers["MEM Rd"] == _Rt)
		sprintf(ip, " fwd_DM-WB_rt_$%d", _Rt), strcat(inp, ip), ReadData2 = exe_readdata2 = registers["MEM ALUout"];
	else if ((_RegWrite==1||_RegWrite==4) && (_Op != 0x05 && _Op != 0x04 && _Op != 0x02 && _Op != 0x03 && !(func == 0x08 && _Op == 0x0)) && registers["MEM RegWrite"] == 2 && registers["MEM Rt"] != 0 && registers["MEM Rt"] == _Rt)
		sprintf(ip, " fwd_DM-WB_rt_$%d", _Rt), strcat(inp, ip), ReadData2 = exe_readdata2 = registers["MEM ALUout"];
	else if ((_RegWrite==1||_RegWrite==4) && registers["MEM RegWrite"] == 3 && registers["MEM Rt"] != 0 && registers["MEM Rt"] == _Rt)
		sprintf(ip, " fwd_DM-WB_rt_$%d", _Rt), strcat(inp, ip), ReadData2 = exe_readdata2 = registers["MDR"];
    else
		exe_readdata2 = reg->getRegister(_Rt);
	return inp ;
}

UINT32 xReadData1, xReadData2;

bool ExecuteStage::execute()
{
	printf("\n--- EX Stage ---\n");
	pc = _pc;
	Op = _Op;
	Rs = _Rs;
	Rt = _Rt;
	Rd = _Rd;
	func_ = func;
	RegWrite = _RegWrite;
    instruction = _instruction;

    ReadData1 = exe_readdata1;
    ReadData2 = exe_readdata2;

	xReadData1 = ReadData1;
	xReadData2 = ReadData2;
	printf("Opcode : %X func: %X shamt: %x\n", Op, func, shamt);
	printf("xReadData1 %X(%X) xReadData2 %X(%X)\n", 0
		, ReadData1, xReadData2, ReadData2);
	printf("Rs: 0x%X, Rt: 0x%X, Rd: 0x%X\n", Rs, Rt, Rd);
	printf("RegWrite: %d\n", RegWrite);
	switcher();
	printf("Instruction: 0x%08x\n", instruction);
	return false;
}

void ExecuteStage::switcher()
{
	UINT32 A = xReadData1;
	UINT32 B = xReadData2;
	int a = A, b = B, negB = twoComplement(B), signImm = SignExtImm(immediate);

	switch (Op)	{
	case 0x0: // R-type
		WriteReg = Rd;
		switch (func) {
		case 0x20: ALUout =   A + B;  break;
		case 0x22: ALUout =   A + negB;  break;
		case 0x24: ALUout =   A & B;  break;
		case 0x25: ALUout =   A | B;  break;
		case 0x26: ALUout =   A ^ B;  break;
		case 0x27: ALUout = ~(A | B); break;
		case 0x28: ALUout = ~(A & B); break;
		case 0x2A: ALUout =  (a < b) ? 1 : 0; break;
		case 0x00: ALUout =   B << shamt; break; // ? NOP
		case 0x02: ALUout =   B >> shamt; break;
		case 0x03: ALUout =   ((int) B) >= 0 ? B >> shamt : (B >> shamt) | ~(0xFFFFFFFF >> shamt); break;
		case 0x08: ALUout =   A; break; // Jr
		default:
			break;
		}
		if (func == 0x20 && isOverflow(A, B)) err_registers[ERR_NUMBER_OVERFLOW] = 1;
		if (func == 0x22 && (isOverflow(A, negB) || B == 0x80000000)) err_registers[ERR_NUMBER_OVERFLOW] = 1;
		printf("R-type ALUout Result: %X (%d op %d)\n", ALUout, A, B);

		break;
	case 0x23: case 0x21: case 0x25: case 0x20: case 0x24: // load
	case 0x2B: case 0x29: case 0x28: // save
		ALUout = A + SignExtImm(immediate);
		printf("A + B = %d + %d = %d\nB = %d", A, SignExtImm(immediate), ALUout, B);
		if (isOverflow(A, SignExtImm(immediate))) err_registers[ERR_NUMBER_OVERFLOW] = 1;
		WriteData = B;
		WriteReg = Rt; break;
	case 0x08:
		ALUout =   A + SignExtImm(immediate);  WriteReg = Rt;
		printf("A + B = %d + %d = %d\n", A, SignExtImm(immediate), ALUout);
		if (isOverflow(A, SignExtImm(immediate))) err_registers[ERR_NUMBER_OVERFLOW] = 1;
		break;
	case 0x0C: ALUout =   A & immediate;  WriteReg = Rt; break;
	case 0x0D: ALUout =   A | immediate;  WriteReg = Rt; break;
	case 0x0E: ALUout = ~(A | immediate); WriteReg = Rt; break;
	case 0x0A: ALUout = a < signImm ? 1 : 0;  WriteReg = Rt; printf("SLTI ----- >%d %d\n", a, signImm); break;
    case LUI: //miss this !
        ALUout = (immediate << 16); WriteReg = Rt; break;
	default: break;
	}
	printf("immediate %X\n", immediate);
	printf("ALUout Result: %X\n", ALUout);
}

bool ExecuteStage::isOverflow(UINT32 a, UINT32 b)
{
	UINT32 sum = a + b;
	if (((a >> 31) ^ (b >> 31)) == 0) // if signs of a, b are the same
		if (((a >> 31) ^ (sum >> 31)) == 1) return true;
	return false;
}

UINT32 ExecuteStage::twoComplement(UINT32 t)
{
		// no need in this project
		//	if (t == 0x80000000) throw ERR_NUMBER_OVERFLOW;
	return ~ t + 1;
}

UINT32 ExecuteStage::SignExtImm(UINT32 t)
{
	// {16{immediate[15]}, immediate}
	if ((t >> 15) == 0x0)
		return t & 0x0000ffff;
	else
		return t | 0xffff0000;
}
/*
UINT32 ExecuteStage::ZeroExtImm(UINT32 t)
{
	// 16{1b'0}, immediate
	return t & 0x0000ffff;
}*/
