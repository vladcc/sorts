/*
	reference: https://www.toptal.com/developers/sorting-algorithms/quick-sort-3-way
*/

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "quick3.h"

#define LCG_MULT 1103515245
#define LCG_INCR 12345
#define LCG_RMAX 0x7FFFFFFF
#define LCG_SHFT 16

#define rand_part(n) ((((((n) * LCG_MULT) + LCG_INCR) >> LCG_SHFT) & LCG_RMAX) % (n))

#define MIN_PART 5

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

typedef struct q3_part {
	size_t left;
	size_t right;
} q3_part;

static void insertion_sort(void * arr, size_t arr_size, size_t elm_size, 
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

static q3_part partition(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{	
	byte_ptr array = arr;
	size_t smaller = 0;
	size_t up = 0;
	size_t down = arr_size - 1;

	size_t piv = rand_part(down);

	byte tmp[elm_size];
	memcpy(tmp, &array[piv*elm_size], elm_size);
	
	int comp_res;
	while(up <= down)
	{	
		comp_res = compar(&array[up*elm_size], tmp);
		
		if (comp_res < 0)
		{
			swap(&array[smaller*elm_size], &array[up*elm_size], elm_size);
			++smaller, ++up;
		}
		else if (comp_res > 0)
		{
			swap(&array[down*elm_size], &array[up*elm_size], elm_size);
			--down;
		}
		else
			++up;
	}
	
	return (q3_part){smaller, up};
}

static void quick_sort_rec(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{	
	if (arr_size < 2)
		return;
	
	byte_ptr start = arr;
	q3_part part; 
	size_t right_size;
	
	while (arr_size > MIN_PART)
	{
		part = partition(start, arr_size, elm_size, compar, swap);
		right_size = arr_size - part.right;
		
		if (part.left < right_size)
		{
			quick_sort_rec(start, part.left, elm_size, compar, swap);
			start += part.right * elm_size;
			arr_size = right_size;
		}
		else
		{
			quick_sort_rec(start + part.right * elm_size, right_size, elm_size, compar, swap);
			arr_size = part.left;
		}
	}
	
	insertion_sort(start, arr_size, elm_size, compar, swap);
	return;
}

void quick3(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	quick_sort_rec(arr, arr_size, elm_size, compar, swap);
	return;
}