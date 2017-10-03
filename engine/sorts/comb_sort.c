#include <stddef.h>
#include <stdbool.h>
#include "comb_sort.h"

typedef unsigned char * byte_ptr;

static void cocktail_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	
	bool swapped;
	byte_ptr start = arr;  
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr prev, next;
	
	for (; start < end; start += elm_size, end -= elm_size)
	{
		swapped = false;
		for (prev = start, next = start + elm_size;
			 next < end; 
			 prev += elm_size, next += elm_size)
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
		
		prev -= elm_size;
		next -= elm_size;
		
		for (; prev >= start; prev -= elm_size, next -= elm_size)
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

void comb_sort(void * arr, size_t arr_size, size_t elm_size, 
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
	
	while (span > 1)
	{
		while (second < end)
		{
			if (compar(first, second) > 0)
				swap(first, second, elm_size);
			
			first += elm_size;
			second += elm_size;
		}
		
		span /= 2;
		first = start;
		second = first + span * elm_size;
	}
	
	cocktail_sort(arr, arr_size, elm_size, compar, swap);
	return;
}