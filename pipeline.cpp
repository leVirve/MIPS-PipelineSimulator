#include "simulator.h"
#ifdef _DEBUG
#define debug_print(s) printf("%s\n", s);
#else 
#define debug_print(s) printf("");
#endif

int main(int argc, char const *argv[])
{
	Simulator* simulator = new Simulator();
	simulator->start();

	debug_print("Smulation ends.");
	getchar();
	return 0;
}