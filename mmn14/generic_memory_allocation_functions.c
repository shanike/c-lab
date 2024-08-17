#include "generic_memory_allocation_functions.h"

/* TODO exit() program */
/* Allocates memory and checks if the allocation was successful */
void *allocate_memory_with_check(long size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        /* Report the memory allocation failure */
        print_system_error(ERROR_STATUS_CODE_100);
    }
    return ptr;
}

/* Free memory only if the pointer is not NULL */
void soft_free_mem(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}