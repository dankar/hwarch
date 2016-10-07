#pragma once

#include <stdint.h>

#define NONE 0
#define REG 1
#define IND 2
#define IND_OFFSET 3
#define IMM 4
#define IMM_16 0x20
#define IMM_32 0x40
#define SYMBOL 0x80
#define IND_32 0x00
#define IND_16 0x0100
#define IND_8  0x0200


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
#define SP 15

extern char *register_names[];
int lookup_reg(const char *name);
