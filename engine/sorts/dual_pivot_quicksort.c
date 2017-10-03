/*
	reference: 
	http://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf
	Vladimir Yaroslavskiy
*/
#include <stddef.h>
#include <string.h>
#include "dual_pivot_quicksort.h"

#define MIN_PART 8
typedef unsigned char byte;
typedef unsigned char * byte_ptr;

static void insertion_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
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

void rec_dual_pivot_quicksort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size))
{
	/* there's probaby a bug somewhere around here */
	if (arr_size < 2)
		return;
	
	if (arr_size <= MIN_PART)
	{
		insertion_sort(arr, arr_size, elm_size, compar, swap);
		return;
	}
	
	byte_ptr array = arr;
	
	size_t up = 0;
	size_t down = arr_size - 1;
	
	size_t piv2 = down-1;
	size_t piv1 = up+1;
	
	int comp_res = compar(&array[piv1*elm_size], &array[piv2*elm_size]);
	if (comp_res > 0)
	{
		swap(&array[piv1*elm_size], &array[down*elm_size], elm_size);
		swap(&array[piv2*elm_size], array, elm_size);
	}
	else
	{
		swap(&array[piv1*elm_size], array, elm_size);
		swap(&array[piv2*elm_size], &array[down*elm_size], elm_size);
	}
	
	byte ppiv_1[elm_size];
	memcpy(ppiv_1, array, elm_size);
	
	byte ppiv_2[elm_size];
	memcpy(ppiv_2, &array[down*elm_size], elm_size);
	
	int curr = up+1;
	int smaller_p1 = up+1;
	int greater_p2 = down-1;
	
	while(curr <= greater_p2)
	{	
		if (compar(&array[curr*elm_size], ppiv_1) < 0)
		{
			swap(&array[smaller_p1*elm_size], &array[curr*elm_size], elm_size);
			++smaller_p1;
		}
		else if (compar(&array[curr*elm_size], ppiv_2) > 0)
		{
			while (curr < greater_p2 && compar(&array[greater_p2*elm_size], ppiv_2) > 0)
				--greater_p2;
			
			swap(&array[greater_p2*elm_size], &array[curr*elm_size], elm_size);
			--greater_p2;
			
			if (compar(&array[curr*elm_size], ppiv_1) < 0)
			{
				swap(&array[smaller_p1*elm_size], &array[curr*elm_size], elm_size);
				++smaller_p1;
			}
		}
		
		++curr;
	}
	
	++greater_p2, --smaller_p1;
	
	swap(array, &array[smaller_p1*elm_size], elm_size);
	swap(&array[down*elm_size], &array[greater_p2*elm_size], elm_size);
	
	int part1_end = smaller_p1;
	int part2_end = greater_p2;
	size_t leq_p2 = greater_p2;
	
	--leq_p2, ++smaller_p1;
	
	curr = smaller_p1;
	while (curr <= leq_p2)
	{
		if (compar(&array[curr*elm_size], ppiv_1) >= 0)
		{
			swap(&array[smaller_p1*elm_size], &array[curr*elm_size], elm_size);
			++smaller_p1;
		}
		else if (compar(&array[curr*elm_size], ppiv_2) <= 0)
		{
			swap(&array[leq_p2*elm_size], &array[curr*elm_size], elm_size);
			--leq_p2;
			
			if (compar(&array[curr*elm_size], ppiv_1) >= 0)
			{
				swap(&array[smaller_p1*elm_size], &array[curr*elm_size], elm_size);
				++smaller_p1;
			}
		}
		++curr;
	}
	
	rec_dual_pivot_quicksort(array, part1_end, elm_size, compar, swap);
	
	if (compar(ppiv_1, ppiv_2) < 0)
		rec_dual_pivot_quicksort(array + (part1_end + 1) * elm_size, part2_end - (part1_end + 1), elm_size, compar, swap);
	
	rec_dual_pivot_quicksort(array + (part2_end + 1) * elm_size, arr_size - (part2_end + 1), elm_size, compar, swap);
	
	return;
}

void dual_pivot_quicksort(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*swap)(void * a, void * b, size_t elm_size))
{
	rec_dual_pivot_quicksort(arr, arr_size, elm_size, compar, swap);
	return;
}