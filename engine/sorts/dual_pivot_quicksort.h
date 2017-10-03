#ifndef DUAL_PIVOT_QUICKSORT_H
#define DUAL_PIVOT_QUICKSORT_H

#include <stddef.h>
void dual_pivot_quicksort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size));
#endif