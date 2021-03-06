#ifndef INSERTION_SORT_MM_H
#define INSERTION_SORT_MM_H

#include <stddef.h>
void insertion_sort_mm(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size));
#endif
