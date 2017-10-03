#ifndef QUICK3_OPT_H
#define QUICK3_OPT_H

#include <stddef.h>
void quick3_opt(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b));
#endif