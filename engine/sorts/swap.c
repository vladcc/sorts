#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swap.h"

void swap_stack(void * a, void * b, size_t elm_size)
{
	typedef unsigned char byte;
	
	byte temp[elm_size];
	// temp = a;
	memcpy(&temp, a, elm_size);
	// a = b;
	memcpy(a, b, elm_size);
	// b = temp;
	memcpy(b, &temp, elm_size);
	
	return;
}

void swap_heap(void * a, void * b, size_t elm_size)
{
	void * temp = malloc(elm_size);

	if (NULL == temp)
	{
		fprintf(stderr, "Err: allocation failed in %s()\n", 
		__func__);
		exit(EXIT_FAILURE);
	}

	// temp = a;
	memcpy(temp, a, elm_size);
	// a = b;
	memcpy(a, b, elm_size);
	// b = temp;
	memcpy(b, temp, elm_size);
	
	free(temp);
	
	return;
}