#include <stddef.h>
#include <stdbool.h>
#include "bubble_sort.h"

void bubble_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	bool swapped;
	byte_ptr start = arr;  
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr prev, next;
	
	for (; start < end; end -= elm_size)
	{
		swapped = false;
		for (prev = start, next = start + elm_size;
			 next < end; 
			 prev = next, next += elm_size)
		{
			if (compar(prev, next) > 0)
			{
				swap(prev, next, elm_size);
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
	}
	
	return;
}