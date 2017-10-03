#include <stddef.h>
#include "heap_sort.h"

#define left(n)    (2*(n))
#define right(n)   (2*(n)+1)
#define parent(n)  ((n)/2)

typedef unsigned char * byte_ptr;

void heapify_array(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	
	byte_ptr heap = (byte_ptr)arr - elm_size;

	// sift down
	int ind_head, ind_curr, le, ri, ind_largest;
	for (ind_head = parent(arr_size); ind_head >= 1; --ind_head)
	{
		ind_curr = ind_head;
		while (ind_curr >= 1)
		{
			le = left(ind_curr);
			ri = right(ind_curr);
			ind_largest = ind_curr;
			
			if (le <= arr_size && 
				compar(&heap[le*elm_size], &heap[ind_largest*elm_size]) > 0)
				ind_largest = le;
			
			if (ri <= arr_size && 
				compar(&heap[ri*elm_size], &heap[ind_largest*elm_size]) > 0)
				ind_largest = ri;
			
			if (ind_largest != ind_curr)
			{
				swap(&heap[ind_curr*elm_size], &heap[ind_largest*elm_size], elm_size);
				ind_curr = ind_largest;
			}
			else
				break;
		}
	}

	return;
}

void heap_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*swap)(void * a, void * b, size_t elm_size))
{
	heapify_array(arr, arr_size, elm_size, compar, swap);
	
	byte_ptr heap = (byte_ptr)arr - elm_size;
	size_t end, head, le, ri, ind_largest;
	
	end = arr_size;
	while (end > 1)
	{
		swap(&heap[1*elm_size], &heap[end*elm_size], elm_size);
		--end;
		head = 1;
		
		while (head < end)
		{
			le = left(head);
			ri = right(head);
				
			ind_largest = head;
			
			if (le <= end && 
				compar(&heap[le*elm_size], &heap[ind_largest*elm_size]) > 0)
				ind_largest = le;
				
			if (ri <= end && 
				compar(&heap[ri*elm_size], &heap[ind_largest*elm_size]) > 0)
				ind_largest = ri;
			
			
			if (head != ind_largest)
			{
				swap(&heap[head*elm_size], &heap[ind_largest*elm_size], elm_size);
				head = ind_largest;
			}
			else
				break;
		}
	}
	
	return;
}