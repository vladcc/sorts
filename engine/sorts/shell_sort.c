#include <stddef.h>
#include "shell_sort.h"

typedef unsigned char * byte_ptr;

void shell_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	size_t span = 1;

	while (span < arr_size)
		span = 2 * span + 1;
	
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	
	byte_ptr first = start;
	byte_ptr second = first + span * elm_size;
	byte_ptr current, prev;
	
	while (span > 0)
	{
		while (second < end)
		{
			for (prev = first, current = second;
				 prev >= start && compar(prev, current) > 0;
				 prev -= span * elm_size, current -= span * elm_size)
			{
				swap(prev, current, elm_size);
			}
				
			first += elm_size;
			second += elm_size;
		}
		
		span /= 2;
		first = start;
		second = first + span * elm_size;
	}
	
	return;
}