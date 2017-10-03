#include <stddef.h>
#include "insertion_sort.h"

void insertion_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr prev, current, next;
	
	for (next = start + elm_size; next < end; next += elm_size)
	{
		for (current = next, prev = current - elm_size; 
			 current > start && compar(prev, current) > 0;
			 current -= elm_size, prev = current - elm_size)
		{
			swap(prev, current, elm_size);
		}
	}
	
	return;
}