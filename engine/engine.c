#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "./sorts/swap.h"
#include "./sorts/quick3_opt.h"
#include "./sorts/quick3.h"
#include "./sorts/quick_sort_m3.h"
#include "./sorts/quick_sort_rand.h"
#include "./sorts/dual_pivot_quicksort.h"
#include "./sorts/shell_sort.h"
#include "./sorts/merge_sort.h"
#include "./sorts/tim_sort.h"
#include "./sorts/heap_sort.h"
#include "./sorts/binary_insertion_sort.h"
#include "./sorts/insertion_sort.h"
#include "./sorts/selection_sort.h"
#include "./sorts/cycle_sort.h"
#include "./sorts/comb_sort.h"
#include "./sorts/cocktail_sort.h"
#include "./sorts/bubble_sort.h"

// TODO: ADD HELP

static const char * argstr[] = {
	"-same", "-up", "-down", "-near", "-rand", "-print", "-config"};

typedef enum arr_opt {
	SAME, UP, DOWN, NEAR_SORT, RANDOM, PRINT, CONFIG} arr_opt;
	
void * make_array(size_t arr_size, size_t elm_size, arr_opt o);

typedef int (*comparf)(const void *, const void *);
typedef void (*swapf)(void * a, void * b, size_t elm_size);
typedef void (*sortf)(void * arr, size_t arr_size, size_t elm_size, 
					  comparf cmp, swapf swp);
typedef void (*sortf_noswp)(void * arr, size_t arr_size, size_t elm_size, 
					  comparf cmp);
					  
typedef struct alg_info {
	sortf sort_func;
	const char * name;
	swapf swap_func;
} alg_info;

static const char * fname = "engine.config.txt";

void run_alg(void * arr, size_t arr_size, size_t elm_size, const char * name, 
			 sortf sort_alg, comparf compar, swapf swap);
			 
int compar(const void * a, const void * b);
void count_swap(void * a, void * b, size_t elm_size);
void count_copy(void * dest, void * source, size_t elm_size); // no const void * to look like a swap()
bool is_sorted(void * arr, size_t arr_size, size_t elm_size,
				int (*compar)(const void * a, const void * b));
				
void print_arr(int * arr, size_t arr_size);
void * emalloc(size_t bytes);


static double compare_count = 0;
static double swap_count = 0;
//static double copy_count = 0;
static void * pgoarr;
static bool gshould_print = false;

void run_alg(void * arr, size_t arr_size, size_t elm_size, const char * name, 
			 sortf sort_alg, comparf compar, swapf swap)
{
	compare_count = 0;
	swap_count = 0;
	
	int * newarr = emalloc(arr_size * elm_size);
	memcpy(newarr, arr, arr_size * elm_size);
	
	printf("\n%s\n", name);
	
	clock_t begin = clock(); 
	if (swap != NULL)
	{
		sort_alg(newarr, arr_size, elm_size, compar, swap);
		printf("Swap: %.0f swaps\n", swap_count);
	}
	else
		((sortf_noswp)sort_alg)(newarr, arr_size, elm_size, compar);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("Comp: %.0f comparisons\n", compare_count);	
	printf("Time: %.3f sec\n", time_spent);
	
	bool is_err = false;
	if (!is_sorted(newarr, arr_size, elm_size, compar))
	{
		fprintf(stderr, "Err: array not sorted properly\n");
		is_err = true;
	}
	
	if (gshould_print)
		putchar('\n'), print_arr(newarr, arr_size);
	
	if (is_err)
	{
		fprintf(stderr, "Print arrays? (y/N): ");
		int ch = tolower(getchar());
		
		if ('y' == ch)
		{
			fprintf(stderr, "\n");
			fprintf(stderr, "Original:\n");
			print_arr(pgoarr, arr_size);
			fprintf(stderr, "After:\n");
			print_arr(newarr, arr_size);
		}
		exit(EXIT_FAILURE);
	}
	
	free(newarr);
	
	return;
}

void * make_array(size_t arr_size, size_t elm_size, arr_opt o)
{
	void * ret = emalloc(arr_size * elm_size);
	
	int * int_arr = ret;
	
	size_t i, j;
	switch (o)
	{
		case RANDOM: 
			srand(time(NULL));
			for (i = 0; i < arr_size; ++i)
				int_arr[i] = rand();
			break;
		case SAME:	
			for (i = 0; i < arr_size; ++i)
				int_arr[i] = 5;
			break;
		case UP: 
			for (i = 0; i < arr_size; ++i)
				int_arr[i] = i+1;
			break;
		case DOWN: 
			for (i = 0, j = arr_size; i < arr_size; ++i, --j)
				int_arr[i] = j;
			break;
		case NEAR_SORT: 
			srand(time(NULL));
			int mod = arr_size / 3 + 1;
			for (i = 0; i < arr_size; ++i)
				int_arr[i] = rand() % mod;
			break;
		default: 
			break;
	}
	
	return ret;
}

int main(int argc, char * argv[])
{
	static const alg_info alg_array[] = {
		{(sortf)qsort, "qsort()", NULL},
		{(sortf)quick3_opt, "quick3_opt()", NULL},
		{quick3, "quick3()", count_swap},
		{quick_sort_rand, "quick_sort_rand()", count_swap},
		{quick_sort_m3, "quick_sort_m3()", count_swap},
		{dual_pivot_quicksort, "dual_pivot_quicksort()", count_swap},
		{tim_sort, "tim_sort()", count_copy},
		{merge_sort, "merge_sort()", count_copy},
		{heap_sort, "heap_sort()", count_swap},
		{shell_sort,  "shell_sort()", count_swap},
		{binary_insertion_sort, "binary_insertion_sort()", count_swap},
		{insertion_sort, "insertion_sort()", count_swap},
		{selection_sort, "selection_sort()", count_swap},
		{cycle_sort, "cycle_sort()", count_swap},
		{comb_sort, "comb_sort()", count_swap},
		{cocktail_sort, "cocktail_sort()", count_swap},
		{bubble_sort, "bubble_sort()", count_swap},
	};

	static const size_t alg_arr_size = sizeof(alg_array) / sizeof(alg_array[0]);
		
	if (argc < 2)
	{
		fprintf(stderr, "Err: no arguments\n");
		exit(EXIT_FAILURE);
	}
	
	size_t arr_size;
	
	if (sscanf(argv[1], "%d", &arr_size) != 1)
	{
		if (strcmp(argv[1], argstr[CONFIG]) == 0)
		{
			FILE * fp;
			
			if ((fp = fopen(fname, "w")) == NULL)
			{
				fprintf(stderr, "Err: couldn't create config file\n");
				exit(EXIT_FAILURE);
			}
			
			fprintf(fp, "# comment\n");
			int i;
			for (i = 0; i < alg_arr_size; ++i)
				fprintf(fp, "%s\n", alg_array[i].name);
			
			fclose(fp);
			
			exit(EXIT_SUCCESS);
		}
		else
			fprintf(stderr, "Err: first argument has to be an int or %s\n", argstr[CONFIG]);
			exit(EXIT_FAILURE);
	}
	
	arr_opt aopt = RANDOM;

	if (argc > 2)
	{
		bool valid_args = false;
		
		int i;
		for (i = SAME; i <= RANDOM; ++i)
		{
			if (strcmp(argv[2], argstr[i]) == 0)
			{
				aopt = i;
				valid_args = true;
				break;
			}
		}
		
		i = 2;
		while (i < argc)
		{
			if (strcmp(argv[i], argstr[PRINT]) == 0)
			{
				gshould_print = true;
				valid_args = true;
			}	
			++i;
		}
		
		if (!valid_args)
		{
			fprintf(stderr, "Err: unrecognized argument: %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}
	
	int * arr = make_array(arr_size, sizeof(*arr), aopt);
	pgoarr = arr;
	
	if (gshould_print)
		print_arr(arr, arr_size);
	
	FILE * fp;
	
	if ((fp = fopen(fname, "r")) == NULL)
	{
		fprintf(stderr, "Err: couldn't open config file\n");
		exit(EXIT_FAILURE);
	}
	
	#define BUFF_SIZE 128
	static char in_buff[BUFF_SIZE];

	while (fgets(in_buff, BUFF_SIZE, fp) != NULL)
	{
		if ('#' == *in_buff || '\n' == *in_buff)
			continue;
		
		char * ch = in_buff;
		
		while (*ch)
		{
			if ('\n' == *ch)
				*ch = '\0';
			++ch;
		}
		
		int i;
		for (i = 0; i < alg_arr_size; ++i)
		{
			if (strcmp(in_buff, alg_array[i].name) == 0)
				run_alg(arr, arr_size, sizeof(*arr), alg_array[i].name, 
						alg_array[i].sort_func, compar, alg_array[i].swap_func);
		}
	}
	
	fclose(fp);
	
	free(arr);
	return 0;
}

void print_arr(int * arr, size_t arr_size)
{
	int i;
	for (i = 0; i < arr_size; ++i)
		fprintf(stderr, "%d ", arr[i]);
	fprintf(stderr, "\n");
	
	return;
}


int compar(const void * a, const void * b)
{
	++compare_count;
	if (*(int*)a > *(int*)b)
		return 1;
	else if (*(int*)a < *(int*)b)
		return -1;
	else
		return 0;
}

void count_swap(void * a, void * b, size_t elm_size)
{
	typedef unsigned char byte;
	
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

void count_copy(void * dest, void * source, size_t elm_size)
{
	++swap_count;
	//++copy_count;
	memcpy(dest, source, elm_size);
	return;
}

bool is_sorted(void * arr, size_t arr_size, size_t elm_size,
				int (*compar)(const void * a, const void * b))
{
	size_t i, prev;
	for (prev = 0, i = 1; i < arr_size; ++i, ++prev)
	{
		if (compar(arr+(prev*elm_size), arr+(i*elm_size)) > 0)
			return false;
	}
	
	return true;
}

void * emalloc(size_t bytes)
{
	void * ret = malloc(bytes);
	if (NULL == ret)
	{
		fprintf(stderr, "Err: allocation failed in function %s()\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	return ret;
}