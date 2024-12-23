#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_MALLOC_CALLS 20000

static size_t total_bytes = 0;
static void *pointers[MAX_MALLOC_CALLS];
static int malloc_calls = 0;

void *_malloc(size_t size)
{
    void *p;

    if (malloc_calls == MAX_MALLOC_CALLS)
    {
        printf("Increase MAX_MALLOC_CALLS!\n");
        exit(-1);
    }

    total_bytes += size;
    p =  malloc(size);
    pointers[malloc_calls++] = p;

    memset(p, 0, size);

    return p;
}

void emancipation_proclamation()
{
    int i;

    for (i = 0; i < malloc_calls; i++)
    {
        free(pointers[i]);
    }
}

void print_malloced_mem()
    {
    printf("Total allocated memory: %zd\n", total_bytes);
    printf("Total allocation calls: %d\n",  malloc_calls);
    }