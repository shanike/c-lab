#ifndef OPERATION_UTILS_H
#define OPERATION_UTILS_H

#include "generic_memory_allocation_functions.h"

/* An operation code with its associated name, arguments number and code. */
typedef struct operation
{
    char *name;     /* The name of the operation */
    int arg_number; /* The number of arguments for the operation */
    int code;       /* The code of the operation */
} operation;

/*
Function to get the operation code of a given string.
Returns 1 if the operation code was found, 0 otherwise.
*/
int get_operation(char *str, operation *op);

/*
Function to free the memory of an operation.
*/
void free_operation(operation *op);

#endif /* OPERATION_UTILS_H */