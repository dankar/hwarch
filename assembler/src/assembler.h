#pragma once

#include <stdint.h>
#include "instructions.h"
#include "cpu_definition.h"

typedef struct
{
	uint8_t *byte_code;
	uint32_t byte_position;
	uint8_t half_byte;
} output_state_t;

const char* read_symbol(const char *code, char *symbol);
const char* read_reg(const char *code, int *reg_out);
const char* read_immediate(const char *code, uint32_t *imm_val, int *error);
void emit_immediate(output_state_t *state, uint32_t imm);
void emit_immediate16(output_state_t *state, uint32_t imm);
void emit_immediate8(output_state_t *state, uint32_t imm);
int emit_code(output_state_t *state, instruction_t *inst);
void emit_variable(output_state_t *state, uint32_t size_in_bytes, uint32_t val);
const char* do_variable(output_state_t *state, uint32_t size_in_bytes, const char *code);
void parse_code(output_state_t *state, const char *code, uint32_t number_of_bytes);