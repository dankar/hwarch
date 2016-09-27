#pragma once

#include <stdint.h>

typedef struct
{
	uint8_t type;
	uint32_t value;
	uint32_t val2;
} argument_t;

typedef struct
{
	const char* operator;
	argument_t arg[3];
	uint8_t op_code;
} instruction_t;

// Defined by generated code
extern instruction_t instructions[];
extern uint32_t number_of_instructions;
