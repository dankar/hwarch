#include "instructions.h"
#include "cpu_definition.h"

instruction_t instructions[] = {
	{ "ld",{ { REG, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x00 },
	{ "ld",{ { REG, 0, 0 },{ IMM | IMM_32, 0, 0 }, },  0x01 },
	{ "ld",{ { REG, 0, 0 },{ IND_32 | IND, 0, 0 },{ NONE, 0, 0 }, },  0x02 },
	{ "ld",{ { IND_32 | IND, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x03 },
	{ "ld",{ { REG, 0, 0 },{ IND_32 | IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x04 },
	{ "ld",{ { IND_32 | IND_OFFSET, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x05 },
	{ "ld",{ { REG, 0, 0 },{ IND_16 | IND, 0, 0 },{ NONE, 0, 0 }, },  0x06 },
	{ "ld",{ { IND_16 | IND, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x07 },
	{ "ld",{ { REG, 0, 0 },{ IND_16 | IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x08 },
	{ "ld",{ { IND_16 | IND_OFFSET, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x09 },
	{ "ld",{ { REG, 0, 0 },{ IND_8 | IND, 0, 0 },{ NONE, 0, 0 }, },  0x0a },
	{ "ld",{ { IND_8 | IND, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x0b },
	{ "ld",{ { REG, 0, 0 },{ IND_8 | IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x0c },
	{ "ld",{ { IND_8 | IND_OFFSET, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x0d },
	{ "xor",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x10 },
	{ "and",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x11 },
	{ "or",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x12 },
	{ "not",{ { REG, 0, 0 },{ REG, 0, 0 },{ NONE, 0, 0 }, },  0x13 },
	{ "add",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x14 },
	{ "add",{ { REG, 0, 0 },{ REG, 0, 0 },{ IMM | IMM_16, 0, 0 }, },  0x15 },
	{ "sub",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x16 },
	{ "shl",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x17 },
	{ "shr",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x18 },
	{ "rol",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x19 },
	{ "ror",{ { REG, 0, 0 },{ REG, 0, 0 },{ REG, 0, 0 }, },  0x1a },
	{ "push",{ { REG, 0, 0 },{ NONE, 0, 0 }, },  0x20 },
	{ "push",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0x21 },
	{ "push",{ { IND_32 | IND_OFFSET, 0, 0 },{ NONE, 0, 0 }, },  0x22 },
	{ "pop",{ { REG, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x23 },
	{ "pop",{ { IND_32 | IND_OFFSET, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x24 },
	{ "hlt",{ { NONE, 0, 0 },{ NONE, 0, 0 },{ NONE, 0, 0 }, },  0x30 },
	{ "call",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0x40 },
	{ "ret",{ { NONE, 0, 0 },{ NONE, 0, 0 }, },  0x41 },
	{ "cmp",{ { REG, 0, 0 },{ REG, 0, 0 }, },  0xef },
	{ "jmp",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf0 },
	{ "jz",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf1 },
	{ "jnz",{ { IMM | IMM_32, 0, 0 },{ NONE, 0, 0 }, },  0xf2 }
};

uint32_t number_of_instructions = sizeof(instructions) / sizeof(instruction_t);