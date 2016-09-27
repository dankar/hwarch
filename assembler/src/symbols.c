#include "symbols.h"
#include <stdio.h>
#include "strings.h"

#define MAX_SYMS 256

symbol_t symbols[MAX_SYMS] = { 0 };
symbol_t symbol_references[MAX_SYMS] = { 0 };

void insert_symbol(const char *instruction, uint32_t position)
{
	int i = 0;
	for (; i < MAX_SYMS; i++)
	{
		if (symbols[i].name[0] == 0)
		{
			strcopy(symbols[i].name, instruction);
			symbols[i].position = position;
			break;
		}
	}

	if (i == MAX_SYMS-1)
	{
		printf("Output of symbols!\n");
		__debugbreak();
	}
}

uint32_t insert_symbol_reference(const char *instruction, uint32_t position)
{
	int i = 0;
	for (; i < MAX_SYMS; i++)
	{
		if (symbol_references[i].name[0] == 0)
		{
			strcopy(symbol_references[i].name, instruction);
			break;
		}
	}

	if (i == MAX_SYMS-1)
	{
		printf("Output of symbol references!\n");
		__debugbreak();
	}

	return i;
}

void resolve_symbols(uint8_t *byte_code)
{
	int i, j;
	uint32_t ptr, value;
	int resolved;

	for (i = 0; i < MAX_SYMS; i++)
	{
		if (symbol_references[i].name[0] != 0)
		{
			ptr = symbol_references[i].position;
			resolved = 0;

			for (j = 0; j < MAX_SYMS; j++)
			{
				if (symbols[j].name[0] != 0)
				{
					if (strcomp(symbols[j].name, symbol_references[i].name))
					{
						value = symbols[j].position;

						if (symbol_references[i].size == 4)
						{
							byte_code[ptr] = (value >> 24) & 0xff;
							byte_code[ptr + 1] = (value >> 16) & 0xff;
							byte_code[ptr + 2] = (value >> 8) & 0xff;
							byte_code[ptr + 3] = (value) & 0xff;
						}
						else if (symbol_references[i].size == 2)
						{
							byte_code[ptr] = (value >> 8) & 0xff;
							byte_code[ptr + 1] = (value) & 0xff;
						}
						else
						{
							printf("Unknown size for symbol\n");
							__debugbreak();
						}
						resolved = 1;
						break;
					}
				}
			}

			if (!resolved)
			{
				printf("Unknown symbol '%s'\n", symbol_references[i].name);
				__debugbreak();
			}
		}
	}

}

void update_symbol_position(uint32_t index, uint32_t position, uint8_t size)
{
	symbol_references[index].position = position;
	symbol_references[index].size = size;
}

