#include "helpers.h"
#include <cstdio>
#include <cstdlib>

void assert(int cond, char *message)
{
	if (!cond)
	{
		printf("%s\n", message);
		__debugbreak();
	}
}
