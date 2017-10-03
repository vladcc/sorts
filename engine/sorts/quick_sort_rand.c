/*
	reference: Mastering Algorithms with C, Kyle Loudon
*/

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "quick_sort_rand.h"

#define LCG_MULT 	1103515245
#define LCG_INCR 	12345
#define LCG_RMAX 	0x7FFFFFFF
#define LCG_SHFT 	16

#define rand_part(n) ((((((n) * LCG_MULT) + LCG_INCR) >> LCG_SHFT) & LCG_RMAX) % (n))

#define MIN_PART 16

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

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

static size_t partition(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{	
	byte_ptr array = arr;
	size_t up = 0;
	size_t down = arr_size - 1;

	size_t piv = rand_part(arr_size);

	byte tmp[elm_size];
	memcpy(tmp, &array[piv*elm_size], elm_size);

	--up, ++down;
	while(1)
	{	
		do
		{
			++up;
		}
		while (compar(&array[up*elm_size], tmp) < 0);
		
		do
		{
			--down;
		}
		while (compar(&array[down*elm_size], tmp) > 0);
		
		if (up >= down)
			break;
		
		swap(&array[up*elm_size], &array[down*elm_size], elm_size);
	}
	
	return up;
}

static void quick_sort_rec(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	if (arr_size < 2)
		return;
	
	byte_ptr start = arr;
	size_t part, right_size;
	
	while (arr_size > MIN_PART)
	{
		part = partition(start, arr_size, elm_size, compar, swap);
		right_size = arr_size - part;
		
		// part is the size of the left half
		if (part < right_size)
		{
			quick_sort_rec(start, part, elm_size, compar, swap);
			start += part * elm_size;
			arr_size = right_size;
		}
		else
		{
			quick_sort_rec(start + part * elm_size, right_size, elm_size, compar, swap);
			arr_size = part;
		}
	}
	
	return;
}

void quick_sort_rand(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	quick_sort_rec(arr, arr_size, elm_size, compar, swap);
	insertion_sort(arr, arr_size, elm_size, compar, swap);
	return;
}