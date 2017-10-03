#include <stddef.h>
#include <string.h>
#include "cycle_sort.h"

void cycle_sort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size))
{
	typedef unsigned char byte;
	typedef unsigned char * byte_ptr;
	
	byte_ptr array = arr;
	
	byte tmp[elm_size];
	
	size_t curr_pos, i, pos;
	size_t end = arr_size - 1;
	
	for (curr_pos = 0; curr_pos < end; ++curr_pos)
	{
		memcpy(tmp, &array[curr_pos*elm_size], elm_size);
		
		pos = curr_pos;
		for (i = pos + 1; i <= end; ++i)
		{
			if (compar(&array[i*elm_size], tmp) < 0)
				++pos;
		}
		
		if (pos == curr_pos)
			continue;
		
		while (compar(&array[pos*elm_size], tmp) == 0)
			++pos;
		
		swap(tmp, &array[pos*elm_size], elm_size);
		
		while (pos != curr_pos)
		{
			pos = curr_pos;
			for (i = pos + 1; i <= end; ++i)
			{
				if (compar(&array[i*elm_size], tmp) < 0)
					++pos;
			}
			
			while (compar(&array[pos*elm_size], tmp) == 0)
				++pos;
			
			swap(tmp, &array[pos*elm_size], elm_size);
		}
	}
	
	return;
}