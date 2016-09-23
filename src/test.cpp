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

	uint8_t machine_code[] = { 0x05, 0x00, 0x12, 0x34, 0x56, 0x78,		// ld R0, 0x12345678
								0x00, 0x10,								// ld R1, R0
								0x05, 0x20, 0x00, 0x00, 0x01, 0x00,		// ld R2, 0x00000100
								0x02, 0x21,								// ld [R2], R1
								0x06, 0x01, 0x20,						// xor r0, r1, r2
								0xf0, 0x00, 0x00, 0x00, 0x00			// jmp 0x00000000
								
	};

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