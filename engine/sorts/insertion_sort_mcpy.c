#include <stddef.h>
#include <string.h>
#include "insertion_sort_mcpy.h"

void insertion_sort_mcpy(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char * byte_ptr;
	typedef unsigned char byte;
	
	byte_ptr start = arr;
	byte_ptr end = start + arr_size * elm_size;
	byte_ptr prev, next;
	byte buff[elm_size];
	
	for (next = start + elm_size; next < end; next += elm_size)
	{
		memcpy(buff, next, elm_size);
		prev = next - elm_size;
		while (prev >= start && compar(prev, buff) > 0)
		{
			memcpy(prev + elm_size, prev, elm_size);
			prev -= elm_size;
		}
		memcpy(prev + elm_size, buff, elm_size);
	}

	return;
}
