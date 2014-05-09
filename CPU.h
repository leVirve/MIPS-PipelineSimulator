
class CPU
{
public:
	CPU();
	~CPU();

private:	
	UINT32 pc;
	UINT32 reg[32];
};