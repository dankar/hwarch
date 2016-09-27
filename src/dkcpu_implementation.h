#pragma once
#include "cpu.h"

uint32_t add(CPU *cpu, uint32_t a, uint32_t b);
uint32_t ld(CPU *cpu, uint32_t a, uint32_t b);
uint32_t sub(CPU *cpu, uint32_t a, uint32_t b);
uint32_t xor (CPU *cpu, uint32_t a, uint32_t b);
uint32_t and (CPU *cpu, uint32_t a, uint32_t b);
uint32_t or (CPU *cpu, uint32_t a, uint32_t b);
uint32_t not (CPU *cpu, uint32_t a, uint32_t b);
uint32_t cmp(CPU *cpu, uint32_t a, uint32_t b);
uint32_t jmp(CPU *cpu, uint32_t a, uint32_t b);
uint32_t jz(CPU *cpu, uint32_t a, uint32_t b);
uint32_t jnz(CPU *cpu, uint32_t a, uint32_t b);
uint32_t shl(CPU *cpu, uint32_t a, uint32_t b);
uint32_t shr(CPU *cpu, uint32_t a, uint32_t b);
uint32_t rol(CPU *cpu, uint32_t a, uint32_t b);
uint32_t ror(CPU *cpu, uint32_t a, uint32_t b);
uint32_t hlt(CPU *cpu, uint32_t a, uint32_t b);
uint32_t push(CPU *cpu, uint32_t a, uint32_t b);
uint32_t pop(CPU *cpu, uint32_t a, uint32_t b);
uint32_t call(CPU *cpu, uint32_t a, uint32_t b);
uint32_t ret(CPU *cpu, uint32_t a, uint32_t b);