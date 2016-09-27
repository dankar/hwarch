#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"
#include "cpu_definition.h"
#include "strings.h"
#include "symbols.h"

const char* read_symbol(const char *code, char *symbol)
{
	code = skip_whitespace(code);

	while (!is_whitespace(code) && *code != '\r' && *code != '\n' && *code != '\'' && *code != ']')
	{
		*symbol++ = *code++;
	}

	*symbol = '\0';

	return code;
}

uint8_t output_byte_code[4096] = { 0 };
int half_byte = 0;
uint32_t output_bytes = 0;

const char* read_reg(const char *code, int *reg_out)
{
	char buff[10];
	int counter = 0;

	code = skip_whitespace(code);

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
	char symbol[256];
	*imm_val = 0;

	code = skip_whitespace(code);

	if (*code != '0')
	{
		code = read_symbol(code, symbol);
		
		*error = SYMBOL;
		*imm_val = insert_symbol_reference(symbol, output_bytes);
		return code;
	}
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
	*error = IMM;
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
		}

		code = read_immediate(code, &imm_val, &tmp);
		if (tmp == -1)
		{
			printf("Invalid immediate in indirect\n");
			__debugbreak();
		}
		if(tmp == SYMBOL)
			argument->type = IND_OFFSET | SYMBOL;
		else
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
	else
	{
		argument->type = IMM;

		code = read_immediate(code, &imm_val, &tmp);
		if (tmp == -1)
		{
			printf("Invalid immediate\n");
			__debugbreak();
		}
		if (tmp == SYMBOL)
			argument->type |= SYMBOL;

		argument->value = imm_val;
		return code;
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

void emit_immediate8(uint32_t imm)
{
	if (half_byte)
	{
		half_byte = 0;
		output_bytes++;
	}
	output_byte_code[output_bytes + 0] = (imm) & 0xff;
	output_bytes += 1;
}

int emit_code(instruction_t *inst)
{
	int found = 0;
	uint32_t i, j;
	

	for (i = 0; i < number_of_instructions; i++)
	{
		if (!strcomp(instructions[i].operator, inst->operator))
			continue;

		found = 1;

		for (j = 0; j < 3; j++)
		{
			if (instructions[i].arg[j].type != (inst->arg[j].type & ~SYMBOL))
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
		uint8_t operand_type = inst->arg[i].type & ~SYMBOL;
		if (operand_type == REG)
		{
			emit_register(inst->arg[i].value);
		}
		else if (operand_type == IMM)
		{
			if (half_byte)
			{
				half_byte = 0;
				output_bytes++;
			}
			if (inst->arg[i].type & SYMBOL)
			{
				update_symbol_position(inst->arg[i].value, output_bytes, 4);
			}
			emit_immediate(inst->arg[i].value);
		}
		else if (operand_type == IND)
		{
			emit_register(inst->arg[i].value);
		}
		else if (operand_type == IND_OFFSET)
		{
			emit_register(inst->arg[i].value);
			
			if (half_byte)
			{
				half_byte = 0;
				output_bytes++;
			}
			if (inst->arg[i].type & SYMBOL)
			{
				update_symbol_position(inst->arg[i].value, output_bytes, 2);
			}
			emit_immediate16(inst->arg[i].val2);
		}
		else if (operand_type == NONE)
		{

		}
		else
		{
			__debugbreak();
		}
	}

	if (half_byte)
	{
		half_byte = 0;
		output_bytes++;
	}

	return 1;
}

void emit_variable(uint32_t size_in_bytes, uint32_t val)
{
	switch (size_in_bytes)
	{
	case 1:
		emit_immediate8(val);
		break;
	case 2:
		emit_immediate16(val);
		break;
	case 4:
		emit_immediate(val);
		break;
	}
}

const char* do_variable(uint32_t size_in_bytes, const char *code)
{
	char instr[512];
	uint32_t imm;
	uint32_t repeat = 1;
	uint32_t i;
	int error;

start:
	code = read_immediate(code, &imm, &error);
	if (error == -1)
	{
		printf("Invalid format for db\n");
		__debugbreak();
	}
	if (error == SYMBOL)
	{
		printf("Unexpected symbol when parsing db\n");
		__debugbreak();
	}

	emit_variable(size_in_bytes, imm);

	if (!is_eol(code))
	{
		if (*code == ',')
		{
			code++;
			goto start;
		}
		else
		{
			code = read_symbol(code, instr);
			if (strcomp(instr, "rep"))
			{
				code = read_immediate(code, &repeat, &error);

				if (error != IMM)
				{
					printf("Syntax error after rep\n");
					__debugbreak();
				}

				for (i = 1; i < repeat; i++)
				{
					emit_variable(size_in_bytes, imm);
				}
			}
			else
			{
				printf("Expected ',' or rep\n");
				__debugbreak();
			}
		}
	}
	
	return goto_next_line(code);
}

void parse_code(const char *code, int number_of_bytes)
{
	int i;
	int state = 0;
	int line_number = 1;
	char instruction[256];
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

		code = read_symbol(code, instruction);
		if (code >= (code_beginning + number_of_bytes)) return;

		if (instruction[strlength(instruction) - 1] == ':')
		{
			instruction[strlength(instruction) - 1] = '\0';
			insert_symbol(instruction, output_bytes);
			continue;
		}

		if (strcomp(instruction, "db"))
		{
			code = do_variable(1, code);
			continue;
		}
		if (strcomp(instruction, "dw"))
		{
			code = do_variable(2, code);
			continue;
		}
		if (strcomp(instruction, "dd"))
		{
			code = do_variable(4, code);
			continue;
		}

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
	uint32_t size = 0, i;
	size_t read;
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

	read = fread(filebuffer, 1, size, fp);

	fclose(fp);

	parse_code(filebuffer, (int)read);

	resolve_symbols(output_byte_code);

	printf("{ ");

	for (i = 0; i < output_bytes; i++)
	{
		printf("0x%02x, ", output_byte_code[i]);
	}

	printf(" };");

	return 0;
}