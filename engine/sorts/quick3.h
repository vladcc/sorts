#ifndef QUICK3_H
#define QUICK3_H

#include <stddef.h>
void quick3(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size));
#endif