#ifndef BINARY_INSERTION_SORT_H
#define BINARY_INSERTION_SORT_H

#include <stddef.h>
void binary_insertion_sort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size));
#endif