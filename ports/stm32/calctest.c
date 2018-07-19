#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "py/objmodule.h"
#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "portmodules.h"
#include "calctest.h"

uint32_t add(uint32_t n1, uint32_t n2)
{
	return n1 + n2;
}

void print_from_lib(const char* str)
{
	mp_obj_t sample_module_obj = mp_module_get(MP_QSTR_c_sample);
	if (sample_module_obj) {
		mp_obj_t sample_print_fn = mp_load_attr(sample_module_obj, MP_QSTR_func_1);
		if (sample_print_fn) {
			mp_call_function_1(sample_print_fn, mp_obj_new_str(str, strlen(str)));
		}
	}
}
