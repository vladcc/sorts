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

#define rand_part(n)\
((((((n) * LCG_MULT) + LCG_INCR) >> LCG_SHFT) & LCG_RMAX) % (n))

#define MIN_PART 16

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

static void * binary_insert_search(void * begin, void * end_incl, void * key,
					size_t elm_size, 
					int (*compar)(const void * a, const void * b))
{
	byte_ptr start = begin;
	byte_ptr end = end_incl;
	byte_ptr mid = start + ((size_t)(end - start) / elm_size / 2) * elm_size;

	while (start <= end)
	{
		if (compar(key, mid) < 0)
			end = mid - elm_size;
		else
			start = mid + elm_size;
		
		mid = start + ((size_t)(end - start) / elm_size / 2) * elm_size;
	}
	
	return (compar(start, key) > 0) ? start : start + elm_size;
}

static void binary_insertion_sort_mm(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size))
{
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr end_sorted = start;
	byte buff[elm_size];
	
	for (byte_ptr next = start + elm_size; next < end; next += elm_size)
	{
		memcpy(buff, next, elm_size);
		end_sorted = binary_insert_search(
			start, next-elm_size, next, elm_size, compar
			);
		
		if (next > end_sorted)
		{
			memmove(end_sorted + elm_size, end_sorted, next - end_sorted);
			memcpy(end_sorted, buff, elm_size);
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
	binary_insertion_sort_mm(arr, arr_size, elm_size, compar, swap);
	return;
}
