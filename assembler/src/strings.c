#include "strings.h"

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
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else return 0;
}

void strcopy(char *dest, const char *src)
{
	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = *src;
}

int strlength(const char *src)
{
	int l = 0;

	while (*src++) l++;

	return l;
}

int strcomp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
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