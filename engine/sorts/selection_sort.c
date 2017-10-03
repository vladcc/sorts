#include <stddef.h>
#include "selection_sort.h"

void selection_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr current, next, target;

	for (current = start; current < end; current += elm_size)
	{
		target = current;
		for (next = current + elm_size; next < end; next += elm_size)
		{
			if (compar(target, next) > 0)
				target = next;
		}
		
		if (target != current)
			swap(target, current, elm_size);
	}
	
	return;
}