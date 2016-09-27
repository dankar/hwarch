#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "instructions.h"
#include "cpu_definition.h"
#include "strings.h"
#include "symbols.h"
#include "assembler.h"

uint8_t output_byte_code[4096] = { 0 };

const char *read_file(const char *filename, uint32_t *file_size)
{
	char *filebuffer;
	size_t read;
	FILE* fp;

	fp = fopen(filename, "rb");

	if (!fp)
		return 0;

	fseek(fp, 0, SEEK_END);
	*file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	filebuffer = (char*)malloc(*file_size);
	read = fread(filebuffer, 1, *file_size, fp);
	fclose(fp);

	if (read != *file_size)
		return 0;

	return filebuffer;
}

int main(int argc, char *argv[])
{
	uint32_t i;
	const char *file1, *file2;
	uint32_t size1, size2;
	output_state_t state;
	
	if (argc != 2)
	{
		printf("usage: as input_file\n");
		exit(0);
	}

	file1 = read_file("test.asm", &size1);
	if (!file1)
	{
		printf("Could not open input file 1\n");
		return 0;
	}
	file2 = read_file("test2.asm", &size2);
	if (!file2)
	{
		printf("Could not open input file 2\n");
		return 0;
	}

	state.byte_code = output_byte_code;
	state.byte_position = 0;
	state.half_byte = 0;

	parse_code(&state, file1, size1);
	parse_code(&state, file2, size2);

	resolve_symbols(output_byte_code);

	printf("{ ");

	for (i = 0; i < state.byte_position; i++)
	{
		printf("0x%02x, ", state.byte_code[i]);
	}

	printf(" };");

	return 0;
}