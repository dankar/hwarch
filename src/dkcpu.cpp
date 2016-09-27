#include "dkcpu.h"

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

void LoadCPUInstructions(CPU *cpu)
{
	// Operation<1 byte opcode, function to call, update_ip, where to put result, parameter 1, parameter 2, optional padding>::Register(&cpu, string for disassembly
	// If update_ip is false, the executor will advance ip if the implementation function returns something other than 0
	// Perform load/mov by adding
	Operation<0x00, ld, true, Register<4>, Register<4>, NullVal<0>, 0> ::Register(cpu, "ld");
	Operation<0x01, ld, true, Register<4>, Indirect<32, Register<4>, NullVal<0>>, NullVal<0>, 0> ::Register(cpu, "ld");
	Operation<0x02, ld, true, Indirect<32, Register<4>, NullVal<0>>, Register<4>, NullVal<0>, 0> ::Register(cpu, "ld");
	Operation<0x03, ld, true, Register<4>, Indirect<32, Register<4>, Immediate<16>>, NullVal<0>, 0> ::Register(cpu, "ld");
	Operation<0x04, ld, true, Indirect<32, Register<4>, Immediate<20>>, Register<4>, NullVal<0>, 4> ::Register(cpu, "ld");
	Operation<0x05, ld, true, Register<4>, NullVal<4>, Immediate<32>, 0> ::Register(cpu, "ld");
	Operation<0x06, xor, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "xor");
	Operation<0x07, and, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "and");
	Operation<0x08, or , true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "or");
	Operation<0x09, not, true, Register<4>, Register<4>, NullVal<0>, 0> ::Register(cpu, "not");
	Operation<0x0a, add, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "add");
	Operation<0x0b, sub, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "sub");
	Operation<0x0c, shl, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "shl");
	Operation<0x0d, shr, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "shr");
	Operation<0x0e, rol, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "rol");
	Operation<0x0f, ror, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "ror");
	Operation<0x20, push, true, NullVal<0>, Register<4>, NullVal<0>, 4> ::Register(cpu, "push");
	Operation<0x21, push, true, NullVal<0>, Immediate<32>, NullVal<0>, 0> ::Register(cpu, "push");
	Operation<0x22, push, true, NullVal<4>, Indirect<32, Register<4>, Immediate<16>>, NullVal<0>, 0> ::Register(cpu, "push");
	Operation<0x23, pop, true, Register<4>, NullVal<0>, NullVal<0>, 4> ::Register(cpu, "pop");
	Operation<0x24, pop, true, Indirect<32, Register<4>, Immediate<20>>, NullVal<0>, NullVal<0>, 0> ::Register(cpu, "pop");
	Operation<0x30, hlt, true, NullVal<0>, NullVal<0>, NullVal<0>, 0> ::Register(cpu, "hlt");
	Operation<0x40, call, false, NullVal<0>, Immediate<32>, NullVal<0>, 0> ::Register(cpu, "call");
	Operation<0x41, ret, false, NullVal<0>, NullVal<0>, NullVal<0>, 0> ::Register(cpu, "ret");
	Operation<0xef, cmp, true, NullVal<0>, Register<4>, Register<4>, 0> ::Register(cpu, "cmp");
	Operation<0xf0, jmp, false, NullVal<0>, Immediate<32>, NullVal<0>, 0> ::Register(cpu, "jmp");
	Operation<0xf1, jz, false, NullVal<0>, Immediate<32>, NullVal<0>, 0> ::Register(cpu, "jz");
	Operation<0xf2, jnz, false, NullVal<0>, Immediate<32>, NullVal<0>, 0> ::Register(cpu, "jnz");
}