#include "instructions.h"
#include "cpu_definition.h"

instruction_t instructions[] = {
	{ "ld",{ { REG, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x00 },
	{ "ld",{ { REG, 0, 0 },{ IND, 0, 0 },{ NONE, 0, 0 }, },  0x01 },
	{ "ld",{ { IND, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x02 },
	{ "ld",{ { REG, 0, 0 },{ IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x03 },
	{ "ld",{ { IND_OFFSET, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x04 },
	{ "ld",{ { REG, 0, 0 },{ IMM | IMM_32, 0, 0 }, },  0x05 },
	{ "xor",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x06 },
	{ "and",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x07 },
	{ "or",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x08 },
	{ "not",{ { REG, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x09 },
	{ "add",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x0a },
	{ "add",{ { REG, 0, 0 },{ REG, 0, 0 },{ IMM | IMM_16, 0, 0 }, },  0x0b },
	{ "sub",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x0c },
	{ "shl",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x0d },
	{ "shr",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x0e },
	{ "rol",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x0f },
	{ "ror",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x10 },
	{ "push",{ { REG, 0, 0 },{ NONE, 0, 0 }, },  0x20 },
	{ "push",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0x21 },
	{ "push",{ { IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x22 },
	{ "pop",{ { REG, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x23 },
	{ "pop",{ { IND_OFFSET, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x24 },
	{ "hlt",{ { NONE, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x30 },
	{ "call",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0x40 },
	{ "ret",{ { NONE, 0, 0 },{ NONE, 0, 0 }, },  0x41 },
	{ "cmp",{ { REG, 0, 0 },{ REG, 0, 0 }, },  0xef },
	{ "jmp",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf0 },
	{ "jz",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf1 },
	{ "jnz",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf2 },
};

uint32_t number_of_instructions = sizeof(instructions) / sizeof(instruction_t);