#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NONE 0
#define REG 1
#define IND 2
#define IND_OFFSET 3
#define IMM 4

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

instruction_t instructions[] = {
	{ "ld",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x00
	},
	{ "ld",{
		{ REG, 0, 0 },
		{ IND, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x01
	},
	{ "ld",{
		{ IND, 0, 0 },
		{ REG, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x02
	},
	{ "ld",{
		{ REG, 0, 0 },
		{ IND_OFFSET, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x03
	},
	{ "ld",{
		{ IND_OFFSET, 0, 0 },
		{ REG, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x04
	},
	{ "ld",{
		{ REG, 0, 0 },
		{ IMM, 0, 0 },
	},
	0x05
	},
	{ "xor",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x06
	},
	{ "and",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x07
	},
	{ "or",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x08
	},
	{ "not",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x09
	},
	{ "add",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0a
	},
	{ "sub",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0b
	},
	{ "shl",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0c
	},
	{ "shr",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0d
	},
	{ "rol",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0e
	},
	{ "ror",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ REG, 0, 0 },
	},
	0x0f
	},
	{ "hlt",{
		{ NONE, 0, 0 },
		{ NONE, 0, 0 },
		{ NONE, 0, 0 },
	},
	0x30
	},
	{ "cmp",{
		{ REG, 0, 0 },
		{ REG, 0, 0 },
		{ NONE, 0, 0 },
	},
	0xef
	},
	{ "jmp",{
		{ IMM, 0, 0 },
		{ NONE, 0, 0 },
	},
	0xf0
	},
	{ "jz",{
		{ IMM, 0, 0 },
		{ NONE, 0, 0 },
	},
	0xf1
	},
	{ "jnz",{
		{ IMM, 0, 0 },
		{ NONE, 0, 0 },
	},
	0xf2
	}
			};
	/*{ "ld",
		{
			{ REG, 0, 0 },
			{ REG, 0, 0 },
			{ NONE, 0, 0 }
		},
		0x00 
	},
	{ "ld",
		{
			{ REG, 0, 0 },
			{ IND, 0, 0 },
			{ NONE, 0, 0 },
		},
		0x01 
	},
	{ "ld", 
		{
			{ IND, 0, 0 },
			{ REG, 0, 0 },
			{ NONE, 0, 0 }
		},
		0x02 
	},
	{ "ld",
		{
			{ REG, 0, 0 },
			{ IND_OFFSET, 0, 0 },
			{ NONE, 0, 0 }
		},
		0x03 
	},
	{ "ld", 
		{
			{ IND_OFFSET, 0, 0 },
			{ REG, 0, 0 },
			{ NONE, 0, 0 }
		},
		0x04 
	},
	{ "ld", 
		{
			{ REG, 0, 0 },
			{ IMM, 0, 0 },
			{ NONE, 0, 0 }
		},
		0x05 
	},
	{ "jmp",
		{
			{ IMM, 0, 0 },
			{ NONE, 0, 0 },
			{ NONE, 0, 0 }
		},
		0xf0
	}
};*/

int strcomp(const char *str1, const char *str2)
{
	while(*str1 && *str2)
	{
		if (*str1 != *str2)
			return 0;
		
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return 0;
	else
		return 1;
}

const char *find_character(const char *str, char chr)
{
	return 0;
}

int is_whitespace(const char *str)
{
	if (*str == '\t' || *str == ' ')
		return 1;
	else
		return 0;
}

const char *skip_whitespace(const char *str)
{
	while (is_whitespace(str))
		str++;
	
	return str;
}

const char *goto_next_line(const char *str)
{
	int nl = 0;

	for (;;)
	{
		if (*str == '\n' || *str == '\r')
		{
			nl = 1;
			break;
		}
		str++;
	}

	while (*str == '\n' || *str == '\r')
		str++;

	return str;
}

int is_eol(const char *str)
{
	if (*str == '#' || *str == '\n' || *str == '\r')
		return 1;
	else
		return 0;
}

const char* get_instruction(const char *code, char *instruction)
{
	while (!is_whitespace(code) && *code != '\r' && *code != '\n')
	{
		*instruction++ = *code++;
	}

	*instruction = '\0';

	return code;
}

#define STATE_EMPTY 0
#define STATE_GOT_INST 0
#define STATE_GOT_A1 0
#define STATE_GOT_A2

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define FLAGS 13
#define R14 14
#define FP 14
#define R15 15
#define SP 15,

uint8_t output_byte_code[4096];
int half_byte = 0;
uint8_t output_bytes = 0;

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

	return -1;
}

const char* read_reg(const char *code, int *reg_out)
{
	char buff[10];
	int counter = 0;
	while (!is_whitespace(code) && !is_eol(code) && *code != ',' && *code != ']' && *code != '+')
	{
		buff[counter] = *code++;
		counter++;
	}

	buff[counter] = '\0';

	*reg_out = lookup_reg(buff);

	return code;
}

int is_hex(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else if (c >= 'a' && c <= 'f')
		return 1;
	else if (c >= 'A' && c <= 'F')
		return 1;
	else
		return 0;
}

uint8_t hex_to_dec(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if(c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else return 0;
}

const char* read_immediate(const char *code, uint32_t *imm_val, int *error)
{
	*imm_val = 0;
	code++;
	if (*code != 'x')
	{
		printf("Invalid imm format\n");
		__debugbreak();
		*error = -1;
	}
	code++;

	while (is_hex(*code))
	{
		*imm_val <<= 4;
		*imm_val += hex_to_dec(*code);
		code++;
	}
	*error = 0;
	return code;
}

const char* get_operand(const char *code, argument_t *argument)
{
	int tmp;
	uint32_t imm_val = 0;
	if (*code == '%')
	{
		// Register
		argument->type = REG;

		code = read_reg(code, &tmp);
		if (tmp == -1)
		{
			printf("Invalid register specified\n");
			__debugbreak();
		}

		argument->value = tmp;
		return code;
	}
	else if (*code == '[')
	{
		code++;
		argument->type = IND;

		code = skip_whitespace(code);

		code = read_reg(code, &tmp);
		if (tmp == -1)
		{
			printf("Invalid format for indirect\n");
			__debugbreak();
		}

		argument->value = tmp;

		code = skip_whitespace(code);
		
		if (*code == ']')
		{
			code++;
			return code;
		}
		if (*code == '+')
		{
			code++;
			code = skip_whitespace(code);
		}

		code = read_immediate(code, &imm_val, &tmp);
		if (tmp == -1)
		{
			printf("Invalid immediate in indirect\n");
			__debugbreak();
		}
		argument->type = IND_OFFSET;
		argument->val2 = imm_val;

		code = skip_whitespace(code);

		if (*code == ']')
		{
			code++;
			return code;
		}
		else
		{
			printf("Expected ] after indirect\n");
			__debugbreak();
		}
	}
	else if (*code == '0')
	{
		argument->type = IMM;

		code = read_immediate(code, &imm_val, &tmp);
		if (tmp == -1)
		{
			printf("Invalid immediate\n");
			__debugbreak();
		}

		argument->value = imm_val;
		return code;
	}
	else
	{
		printf("Unknown parameter for operator\n");
		__debugbreak();
	}
	return 0;
}

int emit_register(uint32_t register_num)
{
	if (half_byte)
	{
		output_byte_code[output_bytes] |= register_num;
		output_bytes++;
		half_byte = 0;
	}
	else
	{
		output_byte_code[output_bytes] = register_num << 4;
		half_byte = 1;
	}

	return 0;
}

void emit_immediate(uint32_t imm)
{
	if (half_byte)
	{
		half_byte = 0;
		output_bytes++;
	}
	output_byte_code[output_bytes + 0] = (imm >> 24) & 0xff;
	output_byte_code[output_bytes + 1] = (imm >> 16) & 0xff;
	output_byte_code[output_bytes + 2] = (imm >> 8) & 0xff;
	output_byte_code[output_bytes + 3] = (imm) & 0xff;
	output_bytes += 4;
}

void emit_immediate16(uint32_t imm)
{
	if (half_byte)
	{
		half_byte = 0;
		output_bytes++;
	}
	output_byte_code[output_bytes + 0] = (imm >> 0x8) & 0xff;
	output_byte_code[output_bytes + 1] = (imm) & 0xff;
	output_bytes += 2;
}

int emit_code(instruction_t *inst)
{
	int found = 0;
	int i, j;
	

	for (i = 0; i < sizeof(instructions) / sizeof(instruction_t); i++)
	{
		if (!strcomp(instructions[i].operator, inst->operator))
			continue;

		found = 1;

		for (j = 0; j < 3; j++)
		{
			if (instructions[i].arg[j].type != inst->arg[j].type)
			{
				found = 0;
			}
		}

		if(found)
			break;
	}

	if (!found)
	{
		printf("Unknown instruction\n");
		return 0;
	}
	output_byte_code[output_bytes++] = instructions[i].op_code;

	for (int i = 0; i < 3; i++)
	{
		if (inst->arg[i].type == REG)
		{
			emit_register(inst->arg[i].value);
		}
		if (inst->arg[i].type == IMM)
		{
			emit_immediate(inst->arg[i].value);
		}
		if (inst->arg[i].type == IND)
		{
			emit_register(inst->arg[i].value);
		}
		if (inst->arg[i].type == IND_OFFSET)
		{
			emit_register(inst->arg[i].value);
			emit_immediate16(inst->arg[i].val2);
		}
	}

	if (half_byte)
	{
		half_byte = 0;
		output_bytes++;
	}

	return 1;
}

void parse_code(const char *code, int number_of_bytes)
{
	int i;
	int state = 0;
	int line_number = 1;
	char instruction[5];
	const char *current_line;
	const char *code_beginning = code;
	instruction_t inst = { 0 };
	argument_t arg = { 0 };

	for (;;)
	{
		for (int i = 0; i < 3; i++)
		{
			inst.arg[i].type = 0;
			inst.arg[i].value = 0;
			inst.arg[i].val2 = 0;
		}
		current_line = code;
		code = skip_whitespace(code);
		if (code >= (code_beginning + number_of_bytes)) return;

		if (is_eol(code))
		{
			code = goto_next_line(code);
			if (code >= (code_beginning + number_of_bytes)) return;
			line_number++;
			continue;
		}

		code = get_instruction(code, instruction);
		if (code >= (code_beginning + number_of_bytes)) return;

		inst.operator = instruction;

		for (i = 0; i < 3; i++)
		{
			code = skip_whitespace(code);
			if (code >(code_beginning + number_of_bytes)) return;

			if (is_eol(code))
			{
				if (!emit_code(&inst))
					printf("%d: %s", line_number, current_line);
				break;
			}
			if ((code = get_operand(code, &arg)))
			{
				inst.arg[i] = arg;
			}
			if (code >= (code_beginning + number_of_bytes)) return;

			code = skip_whitespace(code);
			if (code >= (code_beginning + number_of_bytes)) return;

			if (*code == ',')
				code++;

			if (i == 2)
			{
				if (!emit_code(&inst))
					printf("%d: %s", line_number, current_line);
			}
		}

		code = goto_next_line(code);
		if (code >= (code_beginning + number_of_bytes)) return;
		line_number++;
	}
}

int main(int argc, char *argv[])
{
	char *filebuffer;
	int size = 0;
	FILE* fp;
	if (argc != 2)
	{
		printf("usage: as input_file\n");
		exit(0);
	}

	fp = fopen(argv[1], "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	filebuffer = (char*)malloc(size);

	fread(filebuffer, 1, size, fp);

	fclose(fp);

	parse_code(filebuffer, size);

	

	return 0;
}