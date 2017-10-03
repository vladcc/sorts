#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "tim_sort.h"

#define PART 4
#define MAX_STACK_ALLOC 128

typedef unsigned char byte;
typedef unsigned char * byte_ptr;

double swap_count = 0;

static void count_swap(void * a, void * b, size_t elm_size)
{
	++swap_count;
	
	byte temp[elm_size];
	// temp = a;
	memcpy(&temp, a, elm_size);
	// a = b;
	memcpy(a, b, elm_size);
	// b = temp;
	memcpy(b, &temp, elm_size);
	
	return;
}

static void merge_halves(void * arr, size_t arr_size, size_t div_point, size_t elm_size, 
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
	size_t left_end = div_point;
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

void tim_sort_main(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*copy)(void * a, void * b, size_t elm_size))
{
	byte_ptr run = arr;
	
	size_t i, end, mod;
	
	mod = arr_size % PART;
	end = (mod ? (arr_size - mod) : arr_size);

	for (i = 0; i < end; i += PART)
		insertion_sort(run + i * elm_size, PART, elm_size, compar, count_swap);
	
	if (mod > 1)
		insertion_sort(run + end * elm_size, mod, elm_size, compar, count_swap);
	
	size_t part1 = PART, part2;
	size_t tmp_size;
	
	while (part1 < arr_size)
	{
		i = 0;
		while (1)
		{
			if (i + part1 < arr_size)
			{
				if (i + part1 * 2 < arr_size)
					part2 = part1;
				else
					part2 = arr_size - i - part1;

				tmp_size = part1 + part2;
				merge_halves(run + i * elm_size, tmp_size, part1,
							 elm_size, compar, copy);
				
				i += tmp_size;
			}
			else if (i < arr_size)
			{
				merge_halves(run, arr_size, arr_size - i, elm_size, compar, copy);
				break;
			}
			else
				break;
		}
		
		part1 *= 2;
	}
	
	return;
}

void tim_sort(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b),
					void (*copy)(void * a, void * b, size_t elm_size))
{
	tim_sort_main(arr, arr_size, elm_size, compar, copy);
	printf("Insertion sort swaps: %.0f\n", swap_count);
}