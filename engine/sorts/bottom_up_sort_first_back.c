#include <stddef.h>
#include "bottom_up_sort.h"

void bottom_up_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	byte_ptr start = arr;
	byte_ptr end = arr + arr_size * elm_size;
	int stop = arr_size;
	
	byte_ptr first, next, smallest, smaller;
	
	int step;
	
	while (start < end)
	{
		first = start;
		step = 1;
		next = start + step * elm_size;
		smallest = first;
		smaller = first;
		
		while (step < stop)
		{
			
			if (compar(next, first) < 0)
				smaller = next;
			
			if (compar(smaller, smallest) < 0)
				smallest = smaller;
		
			first += step * elm_size * 2;
			next += step * elm_size * 2;
			
			if (next >= end)
			{
				step *= 2;
				first = start;
				next = start + step * elm_size;
			}
		}

		swap(start, smallest, elm_size);
		start += elm_size; 
		--stop;
	}
	
	return;
}