#include <stddef.h>
#include <string.h>
#include "binary_insertion_sort_mm.h"

typedef unsigned char * byte_ptr;
typedef unsigned char byte;

static void * binary_insert_search(void * begin, void * end_incl, void * key,
					size_t elm_size, 
					int (*compar)(const void * a, const void * b))
{
	byte_ptr start = begin;
	byte_ptr end = end_incl;
	byte_ptr mid = start + ((size_t)(end - start) / elm_size / 2) * elm_size;
	byte buff[elm_size];
	memcpy(buff, key, elm_size);
	
	while (start <= end)
	{
		if (compar(buff, mid) < 0)
			end = mid - elm_size;
		else
			start = mid + elm_size;
		
		mid = start + ((size_t)(end - start) / elm_size / 2) * elm_size;
	}
	
	return (compar(start, buff) > 0) ? start : start + elm_size;
}

void binary_insertion_sort_mm(void * arr, size_t arr_size, size_t elm_size, 
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
