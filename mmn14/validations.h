#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include "global_variables.h"

/* An operation code with its associated name, arguments number and code. */
typedef struct operation
{
    char *name;     /* The name of the operation */
    int arg_number; /* The number of arguments for the operation */
    int code;       /* The code of the operation */
} operation;

/* Function prototypes */

/* Generic function to check if a string is one of the strings in an array */
int is_one_of(char *str_input, char *array[], int array_length);

/* Function to check if a string is an instruction */
int is_directive(char *str);


/*
Function to get the operation code of a given string.
Returns 1 if the operation code was found, 0 otherwise.
*/
int get_opcode(char *str, operation *op);

/* Function to check if a string is a register */
int is_register(char *str);

/*
Function to check if a string is a label.
If is_colon_trimmed is 1, the function will check if the string is a label
without a colon, e.g for instructions using labels.
*/
int is_label(char *str, int is_colon_trimmed);

/* Function to check if a string is a number, for .data directive */
int is_whole_number(char *str);

#endif /* VALIDATIONS_H */
