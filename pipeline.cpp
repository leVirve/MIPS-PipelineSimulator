#include "simulator.h"

int main(int argc, char const *argv[])
{
	freopen("DEBUG_INFO.rpt", "w", stdout);	
	Simulator* simulator = new Simulator();
	simulator->start();

	printf("Smulation ends.");
	return 0;
}
