#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "merge_sort.h"

#define MAX_STACK_ALLOC 128

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

static void merge_halves(void * arr, size_t arr_size, size_t elm_size, 
							int (*compar)(const void * a, const void * b),
							void (*copy)(void * dest, void * array, size_t elm_size))
{
	bool heap_alloc = false;
	size_t alloc_size = arr_size * elm_size;
	
	byte_ptr array = arr;
	byte_ptr tmp;
	
	if (alloc_size > MAX_STACK_ALLOC)
	{
		tmp = (byte_ptr)malloc(alloc_size);
		if (NULL == tmp)
		{
			fprintf(stderr, "Err: allocation failed in function %s()\n", __func__);
			exit(EXIT_FAILURE);
		}
		heap_alloc = true;
	}
	else
		tmp = (byte[MAX_STACK_ALLOC]){0};
	
	size_t le = 0;
	size_t left_end = arr_size / 2;
	size_t ri = left_end;
	size_t ind_merge = 0;
	
	while (le < left_end && ri < arr_size)
	{
		if (compar(&array[le*elm_size], &array[ri*elm_size]) < 0)
			copy(&tmp[ind_merge*elm_size], &array[le*elm_size], elm_size), ++le, ++ind_merge;
		else
			copy(&tmp[ind_merge*elm_size], &array[ri*elm_size], elm_size), ++ri, ++ind_merge;
			
	}
	
	while (le < left_end)
		copy(&tmp[ind_merge*elm_size], &array[le*elm_size], elm_size), ++le, ++ind_merge;
	

	while (ri < arr_size)
		copy(&tmp[ind_merge*elm_size], &array[ri*elm_size], elm_size), ++ri, ++ind_merge;
	
	copy(arr, tmp, elm_size * ind_merge);
	
	if (heap_alloc)
		free(tmp);

	return;
}

void merge_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*copy)(void * dest, void * source, size_t elm_size))
{		
	if (arr_size > 1)
	{
		
		size_t half_size = arr_size / 2;
		byte_ptr second_half = (byte_ptr)arr + half_size * elm_size;
		
		merge_sort(arr, half_size, elm_size, compar, copy);
		merge_sort(second_half, arr_size - half_size, elm_size, compar, copy);
		merge_halves(arr, arr_size, elm_size, compar, copy);
	}
	
	return;
}