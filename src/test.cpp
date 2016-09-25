#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "cpu.h"
#include "helpers.h"
#include "dkcpu.h"

int main(int argc, char *argv[])
{
	CPU cpu(512 * 1024 * 1024);

	LoadCPUInstructions(&cpu);

	uint8_t machine_code[] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x10, 0x00, 0x00, 0x00, 0x0a, 0x06, 0x22, 0x20, 0x05, 0x30, 0x00, 0x00, 0x00, 0x01, 0x0a, 0x22, 0x30, 0xef, 0x21, 0xf2, 0x00, 0x00, 0x00, 0x15, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x10, 0x00, 0x15, 0x04, 0x00, 0x00, 0x15, 0x10, 0x30 };

	cpu.WriteMemory(machine_code, sizeof(machine_code));

	std::stringstream s;
	
	for (;;)
	{
		cpu.Decompile(s);
		std::cout << s.rdbuf() << std::endl;
		cpu.Cycle();
	}

	s.clear();
	
	cpu.PrintState(s);
	std::cout << s.rdbuf();

	assert(0, "end of code");

	return 0;
}