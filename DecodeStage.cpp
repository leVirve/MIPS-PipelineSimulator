#include "DecodeStage.h"

DecodeStage::DecodeStage() :
	_instruction (registers["instruction"]),
	instruction (registers["ID instruction"]),
	_pc (registers["IF PC"]),
	Flush (registers["Flush"]),
	Stall (registers["Stall"]),
	PCSrcD (registers["PCSrc"]),
	PCBranchD (registers["PCBranchD"]),
	PCJumpD (registers["PCJumpD"]),
	pc (registers["ID PC"]),
	Op (registers["ID Op"]),
	func (registers["ID func"]),
	pcCarry (registers["ID PC Carry"]),
	RegWrite (registers["ID RegWrite"]),
	Rs (registers["ID Rs"]),
	Rt (registers["ID Rt"]),
	Rd (registers["ID Rd"]),
	shamt (registers["ID shamt"]),
	immediate (registers["ID immediate"]),
	address (registers["ID address"]),
	ReadData1 (registers["ReadData1"]),
	ReadData2 (registers["ReadData2"]) {
	this->reg = RegisterFile::getInstance();
}
char* DecodeStage::check()
{
    // branch
	iOp = (_instruction >> 26) & 0x3F;
	ifunc = 0x0000003F & _instruction;
	PCSrcD = PC_PLUS4;
	iRs    = (_instruction >> 21) & 0x1F;
	iRt    = (_instruction >> 16) & 0x1F;
	iRd    = (_instruction >> 11) & 0x1F;
	ishamt = (_instruction >>  6) & 0x1F;
	iimmediate  = SignExtImm(_instruction & 0xFFFF);
	iaddress = _instruction & 0x3FFFFFF;
    switch(iOp) {
	case 0x00:
		iRegWrite = 1; break;
	case 0x08: case 0x0F: case 0x0C: case 0x0D: case 0x0E: case 0x0A:
        	iRegWrite = 2; break;
    	case 0x23: case 0x21: case 0x25: case 0x20: case 0x24:
        	iRegWrite = 3; break;
	case 0x2B: case 0x29: case 0x28:
		iRegWrite = 4; break;
    	default: iRegWrite = 0; break;
	}
	Stall=0;
	char* inp = new char[1000];
	char* ip = new char[20];
	sprintf(inp, "%s", dedecode::de(_instruction));
	if(registers["ID Op"]!=0x3F && registers["ID RegWrite"]==3 && (registers["ID Rt"] == iRs||(registers["ID Rt"] == iRt) && iRegWrite != 2) && registers["ID Rt"] != 0)
        strcat(inp, " to_be_stalled"), Stall=1, printf("########## 1\n");
	else if ((iOp == 0x04 || iOp == 0x05) && registers["ID Op"] != 0x3F && registers["ID RegWrite"] == 1 && (registers["ID Rd"] == iRs || registers["ID Rd"] == iRt) && registers["ID Rd"] != 0)
        strcat(inp, " to_be_stalled"), Stall=1, printf("########## 2\n");
	else if ((iOp == 0x04 || iOp == 0x05) && registers["ID Op"] != 0x3F && registers["ID RegWrite"] == 2 && (registers["ID Rt"] == iRs || registers["ID Rt"] == iRt) && registers["ID Rt"] != 0)
        strcat(inp, " to_be_stalled"), Stall=1, printf("########## 3\n");
	else if ((iOp == 0x04 || iOp == 0x05) && registers["EXE Op"] != 0x3F && registers["EXE RegWrite"] == 3 && (registers["EXE Rt"] == iRs || registers["EXE Rt"] == iRt) && registers["EXE Rt"] != 0)
        strcat(inp, " to_be_stalled"), Stall=1, printf("########## 4\n");

    if(!Stall){
		if (registers["EXE RegWrite"] == 1 && registers["EXE Rd"] != 0 && registers["EXE Rd"] == iRs && (iOp == 0x05 || iOp == 0x04))
			sprintf(ip, " fwd_EX-DM_rs_$%d", iRs), strcat(inp, ip), ReadData1 = registers["ALUout"];
		else if ((iOp == 0x05 || iOp == 0x04) && registers["EXE RegWrite"] == 2 && registers["EXE Rt"] != 0 && registers["EXE Rt"] == iRs)
			sprintf(ip, " fwd_EX-DM_rs_$%d", iRs), strcat(inp, ip), ReadData1 = registers["ALUout"];
		else if (registers["MEM RegWrite"] == 3 && registers["MEM instruction"] != 0x0 && registers["MEM Rt"] == iRs)
			ReadData1 = registers["MDR"];
		else if (registers["MEM RegWrite"] == 2 && registers["MEM instruction"] != 0x0 && registers["MEM Rt"] == iRs)
			ReadData1 = registers["MEM ALUout"];
        else if (registers["MEM RegWrite"] == 1 && registers["MEM instruction"] != 0x0 && registers["MEM Rd"] == iRs)
			ReadData1 = registers["MEM ALUout"];
        else
			ReadData1 = reg->getRegister(iRs);
		if (registers["EXE RegWrite"] == 1 && registers["EXE Rd"] != 0 && registers["EXE Rd"] == iRt && (iOp == 0x05 || iOp == 0x04))
			sprintf(ip, " fwd_EX-DM_rt_$%d", iRt), strcat(inp, ip), ReadData2 = registers["ALUout"];
		else if ((iOp == 0x05 || iOp == 0x04) && registers["EXE RegWrite"] == 2 && registers["EXE Rt"] != 0 && registers["EXE Rt"] == iRt)
			sprintf(ip, " fwd_EX-DM_rt_$%d", iRt), strcat(inp, ip), ReadData2 = registers["ALUout"];
		else if (registers["MEM RegWrite"] == 3 && registers["MEM instruction"] != 0x0 && registers["MEM Rt"] == iRt)
			ReadData2 = registers["MDR"];
		else if (registers["MEM RegWrite"] == 2 && registers["MEM instruction"] != 0x0 && registers["MEM Rt"] == iRt)
			ReadData2 = registers["MEM ALUout"];
		else if (registers["MEM RegWrite"] == 1 && registers["MEM instruction"] != 0x0 && registers["MEM Rd"] == iRt)
			ReadData2 = registers["MEM ALUout"];
		else
			ReadData2 = reg->getRegister(iRt);
		if (iOp == 0x04) if (ReadData1 == ReadData2) PCtemp = _pc + BranchAdrr(iimmediate), PCSrcD = PC_BRANCH;
		if (iOp == 0x05) if (ReadData1 != ReadData2) PCtemp = _pc + BranchAdrr(iimmediate), PCSrcD = PC_BRANCH;
        // Jump
        Flush = 0;
        if (iOp == 0x00 && ifunc == 0x08) PCtemp = pcCarry = ReadData1, PCSrcD = PC_JUMP; // jr
		if (iOp == 0x02) PCtemp = JumpAddr(iaddress, _pc), PCSrcD = PC_JUMP; // j
		if (iOp == 0x03) PCtemp = JumpAddr(iaddress, _pc), PCSrcD = PC_JUMP; // jal

        if(iOp == 0x05||iOp == 0x04){
			if (PCSrcD == PC_BRANCH/*&&_pc!=PCtemp*/) Flush = 1; /*** WTF!!!!!!!!!!! TA is THUNDERING */
        }
        else if((ifunc==0x08 && iOp==0x0)||iOp == 0x02||iOp == 0x03){
            Flush = 1;
        }
	}
    return inp;
}

bool DecodeStage::execute()
{

	/*------------------*/

	pc = _pc;
	if(Stall){
        Rs=0;
        Rt=0;
        Rd=0;
        instruction=0;
        Op=0;
        func=0;
        shamt=0;
        immediate=0;
        address=0;
    }else {
        instruction = _instruction;
        Rs=iRs;
        Rt=iRt;
        Rd=iRd;
        Op=iOp;
        func=ifunc;
        shamt=ishamt;
        immediate=iimmediate;
        address=iaddress;
        RegWrite=iRegWrite;
    }
	/*
	if (registers["MEM RegWrite"] && registers["MEM Rd"] != 0 && registers["MEM Rd"] == Rs) {
		printf("ID ForwadA = 10\n");
	}
	if (registers["MEM RegWrite"] && registers["MEM Rd"] != 0 && registers["MEM Rd"] == Rt) {
		printf("ID ForwadB = 10\n");
	}*/
	if((iOp == 0x05&&ReadData1 != ReadData2)||(iOp == 0x04&&ReadData1 == ReadData2)) {PCBranchD = PCtemp, PCSrcD = PC_BRANCH;}
	//if((ifunc == 0x08&&iOp==0x0)||iOp == 0x02||iOp == 0x03) PCJumpD = PCtemp, PCSrcD = PC_JUMP;

	if (iOp == 0x00 && ifunc == 0x08) PCJumpD = PCtemp, PCSrcD = PC_JUMP; // jr
	if (iOp == 0x02) PCJumpD = PCtemp, PCSrcD = PC_JUMP; // j
	if (iOp == 0x03) PCJumpD = PCtemp, PCSrcD = PC_JUMP; // jal
    if(iOp == 0x04 || iOp == 0x05) if (isOverflow(_pc, BranchAdrr(immediate))) err_registers[ERR_NUMBER_OVERFLOW] = 1;
	printf("\n--- ID Stage ---\n");
	printf("<<<<%X>>>>\n", PCtemp);
	printf("Opcode = %X func = %X\n", Op, func);
	printf("PCSrc = %d\n", PCSrcD);
	printf("Rs: 0x%d, Rt: 0x%d, Rd: 0x%d\n", Rs, Rt, Rd);
	printf("Imm: 0x%X(%d) Address: 0x%X\n", immediate, (int)immediate, address);
	printf("%X + %X = %X\n", _pc, BranchAdrr(immediate), BranchAdrr(immediate) + _pc);
	printf("ReadData1: 0x%X\tReadData2: 0x%X\n", ReadData1, ReadData2);
	printf("Instruction: 0x%08x\n", instruction);
	return false;
}

UINT32 DecodeStage::SignExtImm(UINT32 t)
{
	// {16{immediate[15]}, immediate}
	if ((t >> 15) == 0x0) return t & 0x0000ffff;
	else return t | 0xffff0000;
}

UINT32 DecodeStage::BranchAdrr(UINT32 t)
{
	// BranchAddr = {14{immediate[15]}, immediate, 2'b0}
	if ((t >> 15) == 0x0)
		return 0x0003ffff & (t << 2);
	else
		return 0xfffc0000 | (t << 2);
}

UINT32 DecodeStage::JumpAddr(UINT32 t, UINT32 _pc)
{
	// JumpAddr = {PC[31:28], address, 2'b0}
	//* already +4 after fetch
	UINT32 addr = _pc & 0xf0000000;
	return addr | (t << 2);
}
bool DecodeStage::isOverflow(UINT32 a, UINT32 b)
{
	UINT32 sum = a + b;
	if (((a >> 31) ^ (b >> 31)) == 0) // if signs of a, b are the same
		if (((a >> 31) ^ (sum >> 31)) == 1) return true;
	return false;
}