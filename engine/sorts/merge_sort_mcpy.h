#ifndef MERGE_SORT_MCPY_H
#define MERGE_SORT_MCPY_H

#include <stddef.h>
void merge_sort_mcpy(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*copy)(void * a, void * b, size_t elm_size));
#endif
