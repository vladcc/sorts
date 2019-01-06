#include <stddef.h>
#include "binary_insertion_sort.h"

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

void binary_insertion_sort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size))
{
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr end_sorted = start;
	
	byte_ptr current, next, selected;
	for (current = start, next = current + elm_size; 
		 next < end;
		 current += elm_size, next += elm_size)
	{
		selected = next;
		end_sorted = binary_insert_search(start, current, selected, elm_size, compar);
	
		while (selected > end_sorted)
			swap(selected, selected - elm_size, elm_size), selected -= elm_size;
	}
	
	return;
}
