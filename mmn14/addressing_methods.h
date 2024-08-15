#include "./memory_table.h"

enum addressing_methods
{
    IMMEDIATE = 0,
    DIRECT = 1,
    INDIRECT_REGISTER = 2,
    DIRECT_REGISTER = 3,
    INVALID = -1
    /* UNSET = -2 */
};

enum arg_index
{
    FIRST_ARG = 0,
    SECOND_ARG = 1
};

/*
Returns the addressing method of the given argument.
If the argument is invalid, prints an error message and returns INVALID.

*/
int find_addressing_method(char arg[], location_in_file file_location);
