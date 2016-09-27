#include "dkcpu_implementation.h"

uint32_t add(CPU *cpu, uint32_t a, uint32_t b)
{
	uint64_t res = a + b;
	if (res > ((2ULL << 32) - 1))
		cpu->m_state.registers[CPU::FLAGS] |= CPU::CARRY;
	else
		cpu->m_state.registers[CPU::FLAGS] &= ~CPU::CARRY;

	return a + b;
}

uint32_t ld(CPU *cpu, uint32_t a, uint32_t b)
{
	return a + b;
}

uint32_t sub(CPU *cpu, uint32_t a, uint32_t b)
{
	return a - b;
}

uint32_t xor (CPU *cpu, uint32_t a, uint32_t b)
{
	return a ^ b;
}

uint32_t and (CPU *cpu, uint32_t a, uint32_t b)
{
	return a & b;
}

uint32_t or (CPU *cpu, uint32_t a, uint32_t b)
{
	return a | b;
}

uint32_t not (CPU *cpu, uint32_t a, uint32_t b)
{
	return ~a;
}

uint32_t cmp(CPU *cpu, uint32_t a, uint32_t b)
{
	return sub(cpu, a, b);
}

uint32_t jmp(CPU *cpu, uint32_t a, uint32_t b)
{
	cpu->m_state.ip = a;
	return 0;
}

uint32_t jz(CPU *cpu, uint32_t a, uint32_t b)
{
	if (cpu->m_state.registers[CPU::FLAGS] & CPU::ZERO)
	{
		cpu->m_state.ip = a;
		return 0;
	}
	else
	{
		return 1;
	}	
}

uint32_t jnz(CPU *cpu, uint32_t a, uint32_t b)
{
	if ((cpu->m_state.registers[CPU::FLAGS] & CPU::ZERO) == 0)
	{
		cpu->m_state.ip = a;
		return 0;
	}
	else
	{
		return 1;
	}
}

uint32_t shl(CPU *cpu, uint32_t a, uint32_t b)
{
	return a << b;
}

uint32_t shr(CPU *cpu, uint32_t a, uint32_t b)
{
	return a >> b;
}

uint32_t rol(CPU *cpu, uint32_t a, uint32_t b)
{
	uint32_t save = (a >> (32 - b) & ((2UL << b) - 1));

	return (a << b) | save;
}

uint32_t ror(CPU *cpu, uint32_t a, uint32_t b)
{
	uint32_t save = (a & ((2UL << b) - 1) << (32 - b));
	return (a >> b) | save;
}

uint32_t hlt(CPU *cpu, uint32_t a, uint32_t b)
{
	for (;;)
	{
		__debugbreak();
	}
}

uint32_t push(CPU *cpu, uint32_t a, uint32_t b)
{
	cpu->m_state.registers[CPU::SP] -= 4;
	cpu->WriteMemory32(cpu->m_state.registers[CPU::SP], a);

	return 0;
}

uint32_t pop(CPU *cpu, uint32_t a, uint32_t b)
{
	uint32_t value = cpu->ReadMemory32(cpu->m_state.registers[CPU::SP]);
	cpu->m_state.registers[CPU::SP] += 4;

	return value;
}

uint32_t call(CPU *cpu, uint32_t a, uint32_t b)
{
	push(cpu, cpu->m_state.ip + 5, 0);
	cpu->m_state.ip = a;

	return 0;
}

uint32_t ret(CPU *cpu, uint32_t a, uint32_t b)
{
	cpu->m_state.ip = pop(cpu, a, b);
	return 0;
}