#include "dkcpu_definition.h"
#include "dkcpu_implementation.h"

// This list is automatically generated, don't edit it here
void LoadCPUInstructions(CPU *cpu)
{
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
	Operation<0x0b, add, true, Register<4>, Register<4>, Immediate<16>, 0> ::Register(cpu, "add");
	Operation<0x0c, sub, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "sub");
	Operation<0x0d, shl, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "shl");
	Operation<0x0e, shr, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "shr");
	Operation<0x0f, rol, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "rol");
	Operation<0x10, ror, true, Register<4>, Register<4>, Register<4>, 4> ::Register(cpu, "ror");
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
