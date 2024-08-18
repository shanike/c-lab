#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "global_variables.h"
#include "generic_memory_allocation_functions.h"
#include "operation_utils.h"

/* Function prototypes */

/* Generic function to check if a string is one of the strings in an array */
int is_one_of(char *str_input, char *array[], int array_length);

/* Function to check if a string is an instruction */
int is_directive(char *str);

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

/*
Returns 1 if the given string is a valid immediate number, 0 otherwise.
An immediate addressing method value goes into 13 bits, so it must be between -2048 and 2047.
*/
int validate_immediate_number(char *str, location_in_file file_location);

#endif /* VALIDATIONS_H */
