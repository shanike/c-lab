#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include "global_variables.h"

/* An operation code with its associated opcode and arguments number */
typedef struct op_code {
    char *opcode;    /* The opcode of the operation */
    int arg_number;  /* The number of arguments for the operation */
} op_code;

/* Function prototypes */

/* Generic function to check if a string is one of the strings in an array */
int is_one_of(char *str_input, char *array[], int array_length);

/* Function to check if a string is an instruction */
int is_instruction(char *str);

/* Function to check if a string is an opcode */
int is_opcode(char *str);

/* Function to check if a string is a register */
int is_register(char *str);

#endif /* VALIDATIONS_H */
