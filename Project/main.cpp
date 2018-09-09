#include "global.h"
#include "user.h"

void main(int argc, char* argv[])
{
	inic();
	userMain(argc, argv);
	restore();
}
