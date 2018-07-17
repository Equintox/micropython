#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "calctest.h"

uint32_t add(uint32_t n1, uint32_t n2)
{
	return n1 + n2;
}

void print_from_lib(const char* str)
{
	printf("String printed from C-Lib: %s\n",str);
}
