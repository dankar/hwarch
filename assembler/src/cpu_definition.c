#include "cpu_definition.h"
#include "strings.h"

char *register_names[] = { "%r0", "%r1", "%r2", "%r3", "%r4", "%r5", "%r6", "%r7", "%r8", "%r9", "%r10", "%r11", "%r12", "%r13", "%r14", "%r15" };

int lookup_reg(const char *name)
{
	int i = 0;
	for (; i < 16; i++)
	{
		if (strcomp(name, register_names[i]))
		{
			return i;
		}
	}

	if (strcomp(name, "%flags"))
		return 13;
	if (strcomp(name, "%fp"))
		return 14;
	if (strcomp(name, "%sp"))
		return 15;

	return -1;
}