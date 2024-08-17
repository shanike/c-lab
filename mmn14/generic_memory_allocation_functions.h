#include "error_handling.h"

/**
 * Allocates memory and checks if the allocation was successful.
 *
 * @param size The size of the memory to allocate.
 * @return Pointer to the allocated memory if successful, or NULL if the allocation fails.
 */
void *allocate_memory_with_check(long size);

/**
 * Frees memory only if the pointer is not NULL.
 *
 * @param ptr The pointer to the memory to free.
 */
void soft_free_mem(void *ptr);