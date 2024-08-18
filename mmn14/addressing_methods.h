#ifndef ADDRESSING_METHODS_H
#define ADDRESSING_METHODS_H

#include "memory_table.h"
#include "validations.h"
#include "error_handling.h"

enum AddressingMethods
{
    IMMEDIATE = 0,
    DIRECT = 1,
    INDIRECT_REGISTER = 2,
    DIRECT_REGISTER = 3,
    INVALID = -1
    /* UNSET = -2 */
};
typedef enum AddressingMethods AddressingMethods_t;

enum arg_index
{
    FIRST_ARG = 0,
    SECOND_ARG = 1
};

/*
Returns the addressing method of the given argument.
If the argument is invalid, prints an error message and returns INVALID.
*/
AddressingMethods_t find_addressing_method(char arg[], location_in_file file_location);

#endif
