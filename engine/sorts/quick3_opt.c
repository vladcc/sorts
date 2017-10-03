/*
	optimization reference: 
	https://code.woboq.org/userspace/glibc/stdlib/qsort.c.html
	Robert Sedgewick, Algorithms in C
*/
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "quick3_opt.h"

#define LCG_MULT 	1103515245
#define LCG_INCR 	12345
#define LCG_RMAX 	0x7FFFFFFF
#define LCG_SHFT 	16

#define rand_part(n) ((((((n) * LCG_MULT) + LCG_INCR) >> LCG_SHFT) & LCG_RMAX) % (n))

#define MIN_PART 	5
#define MAX_STACK					(CHAR_BIT * sizeof(size_t))
#define POP(part_start, part_sz)	((void) (--top, (part_start = top->start), (part_sz = top->size)))
#define PUSH(part_start, part_sz)	((void) ((top->start = (part_start)), (top->size = (part_sz)), ++top))
#define STACK_EMPTY					(stack >= top)

#define SWAP(a, b, el_size)\
	do\
	{\
	  register size_t size = (el_size);\
	  register byte_ptr pa = (a);\
	  register byte_ptr pb = (b);\
	  while (size > 0)\
	  {\
		  byte tmp = *pa;\
		  *pa++ = *pb;\
		  *pb++ = tmp;\
		  --size;\
	   }\
	} while (0)

#define CPY(dest, src, el_size)\
	do\
	{\
	  register size_t size = (el_size);\
	  register byte_ptr d = (dest);\
	  register byte_ptr s = (src);\
	  while (size > 0)\
	  {\
		  *d++ = *s++;\
		  --size;\
	   }\
	} while (0)
		
typedef unsigned char byte;
typedef unsigned char * byte_ptr;

typedef struct q3_part_stack {
	byte_ptr start;
	size_t size;
} q3_part_stack;

void quick3_opt(void * arr, size_t arr_size, size_t elm_size, 
					int (*compar)(const void * a, const void * b))
{
	if (arr_size < 2)
		return;
	
	// stack
	q3_part_stack stack[MAX_STACK];
	q3_part_stack * top = stack;
	
	byte_ptr curr_start = arr;
	
	// holds current pivot value
	byte tmp[elm_size];
	
	// insertion sort variables
	byte_ptr end, prev, current, next;
	
	// partition variables
	size_t smaller, up, down, piv;
	int comp_res;
	
	// other
	size_t right_size, curr_size;
	
	curr_size = arr_size;
	while (true)
	{
		while (curr_size > MIN_PART)
		{
			/* ---  partition --- */
			smaller = up = 0;
			down = curr_size - 1;
			piv = rand_part(down);
			
			CPY(tmp, &curr_start[piv*elm_size], elm_size);

			while(up <= down)
			{	
				comp_res = compar(&curr_start[up*elm_size], tmp);
				
				if (comp_res < 0)
				{
					SWAP(&curr_start[smaller*elm_size], &curr_start[up*elm_size], elm_size);
					++smaller, ++up;
				}
				else if (comp_res > 0)
				{
					SWAP(&curr_start[down*elm_size], &curr_start[up*elm_size], elm_size);
					--down;
				}
				else
					++up;
			}
			/* --- /partition --- */
			
			right_size = curr_size - up;
			
			if (smaller < right_size)
			{
				PUSH((curr_start + up * elm_size), right_size);
				curr_size = smaller;
			}
			else
			{
				PUSH(curr_start, smaller);
				curr_start = curr_start + up * elm_size;
				curr_size = right_size;
			}
		}
	
		/* ---  insertion sort --- */
		end = curr_start + curr_size * elm_size;
		for (next = curr_start + elm_size; next < end; next += elm_size)
		{
			for (current = next, prev = current - elm_size; 
				 current > curr_start && compar(prev, current) > 0;
				 current -= elm_size, prev = current - elm_size)
			{
				SWAP(prev, current, elm_size);
			}
		}
		/* --- /insertion sort --- */
		
		if (STACK_EMPTY)
			break;
		
		POP(curr_start, curr_size);
	}
	
	return;
}