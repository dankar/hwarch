#pragma once

#include <stdint.h>

void strcopy(char *dest, const char *src);
int strlength(const char *src);
int strcomp(const char *str1, const char *str2);
int is_whitespace(const char *str);
const char *skip_whitespace(const char *str);
const char *goto_next_line(const char *str);
int is_eol(const char *str);
int is_hex(char c);
uint8_t hex_to_dec(char c);