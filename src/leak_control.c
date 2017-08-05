#include "lem-in.h"

int malloc_counter = 0;

void *my_malloc(size_t size)
{
    malloc_counter++;
    return malloc(size);
}

void my_free(void *ptr)
{
    free(ptr);
    malloc_counter--;
}
