#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "quick_sort_m3.h"

#define MIN_PART 20

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

static bool cocktail_shuffle(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	bool swapped = false;
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	
	byte_ptr prev, next;
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
		return false;
	
	for (next = end - elm_size * 2, prev = next - elm_size; 
		 prev >= start; 
		 next -= elm_size, prev -= elm_size)
	{
		if (compar(prev, next) > 0)
			swap(prev, next, elm_size);
	}
	
	for (start += elm_size, end -= elm_size * 2; 
		 start < end;
		 start += elm_size, end -= elm_size)
	{
		if (compar(start, end) > 0)
			swap(start, end, elm_size);
	}
	
	return true;
}

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
	size_t mid = arr_size / 2;
	size_t down = arr_size - 1;
	
	if (compar(array, &array[mid*elm_size]) > 0)
		swap(array, &array[mid*elm_size], elm_size);
	
	if (compar(&array[mid*elm_size], &array[down*elm_size]) > 0)
		swap(&array[mid*elm_size], &array[down*elm_size], elm_size);
	else
		goto jump_over;
	
	if (compar(&array[up*elm_size], &array[mid*elm_size]) > 0)
		swap(&array[up*elm_size], &array[mid*elm_size], elm_size);
	
	jump_over:
	swap(&array[mid*elm_size], &array[down*elm_size], elm_size);
	
	byte_ptr piv = &array[down*elm_size];

	--up, ++down;
	while(1)
	{	
		do
		{
			++up;
		}
		while (compar(&array[up*elm_size], piv) < 0);
		
		do
		{
			--down;
		}
		while (compar(&array[down*elm_size], piv) > 0);
		
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
	
	insertion_sort(start, arr_size, elm_size, compar, swap);
	
	return;
}

void quick_sort_m3(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	if (!cocktail_shuffle(arr, arr_size, elm_size, compar, swap))
		return;
	
	quick_sort_rec(arr, arr_size, elm_size, compar, swap);
	
	return;
}