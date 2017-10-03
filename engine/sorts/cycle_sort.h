#ifndef CYCLE_SORT_H
#define CYCLE_SORT_H

#include <stddef.h>
void cycle_sort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size));
#endif