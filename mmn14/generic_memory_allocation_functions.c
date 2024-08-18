#include "generic_memory_allocation_functions.h"

/*
Allocates memory and checks if the allocation was successful
If the allocation fails, the function prints an error message and exits the program
*/
void *allocate_memory_with_check(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        /* Report the memory allocation failure */
        print_system_error(ERROR_STATUS_CODE_100);
        exit(EXIT_FAILURE);
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
