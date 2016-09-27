#pragma once

#include <stdint.h>

typedef struct
{
	char name[256];
	uint32_t position;
	uint32_t size;
} symbol_t;


void insert_symbol(const char *instruction, uint32_t position);
uint32_t insert_symbol_reference(const char *instruction, uint32_t position);
void resolve_symbols(uint8_t *byte_code);
void update_symbol_position(uint32_t index, uint32_t position, uint8_t size);