#ifndef TIM_SORT_H
#define TIM_SORT_H

#include <stddef.h>
void tim_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*copy)(void * a, void * b, size_t elm_size));
#endif