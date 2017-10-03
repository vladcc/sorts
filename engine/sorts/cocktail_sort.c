#include <stddef.h>
#include <stdbool.h>
#include "cocktail_sort.h"

void cocktail_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	bool swapped = true;
	byte_ptr start = arr;  
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr prev, next;
	
	prev = start;
	next = start + elm_size;
	
	while (swapped)
	{
		swapped = false;
		for (; next < end; prev += elm_size, next += elm_size)
		{
			if (compar(prev, next) > 0)
			{
				swap(prev, next, elm_size);
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
		
		swapped = false;
		
		end -= elm_size;
		next = end - elm_size;
		prev = next - elm_size;
		
		for (; prev >= start; prev -= elm_size, next -= elm_size)
		{
			if (compar(prev, next) > 0)
			{
				swap(prev, next, elm_size);
				swapped = true;
			}
		}
		
		start += elm_size;
		prev = start;
		next = prev + elm_size;
	}
	
	return;
}