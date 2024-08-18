#include "addressing_methods.h"

AddressingMethods_t find_addressing_method(char arg[], location_in_file file_location)
{
    if (arg[0] == '#')
    {
        if (!is_whole_number(arg + 1))
        {
            print_file_error(ERROR_STATUS_CODE_120, file_location, arg);
            return INVALID;
        }
        if (!validate_immediate_number(arg + 1, file_location))
        {
            return INVALID;
        }
        return IMMEDIATE;
    }
    else if (arg[0] == '*')
    {
        if (!is_register(arg + 1))
        {
            print_file_error(ERROR_STATUS_CODE_121, file_location, arg);
            return INVALID;
        }
        return INDIRECT_REGISTER;
    }
    else if (is_register(arg))
    {
        return DIRECT_REGISTER;
    }
    else if (is_label(arg, 1))
    {
        return DIRECT;
    }
    print_file_error(ERROR_STATUS_CODE_122, file_location, arg);
    return INVALID;
}
