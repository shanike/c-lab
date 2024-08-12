#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "./generic_file_functions.h"
#include "./error_handling.h"

/* The Following array specifies the error status code numbers and the corresponding error message. */
Error errors[] = {
    {ERROR_STATUS_CODE_100, "Failed to dynamically allocate memory"},
    {ERROR_STATUS_CODE_101, "Failed to open new file for writing"},
    {ERROR_STATUS_CODE_102, "Failed to open file for reading"},
    {ERROR_STATUS_CODE_103, "Error - macro without name definition"},
    {ERROR_STATUS_CODE_104, "Error - extra text after macro name definition"},
    {ERROR_STATUS_CODE_105, "Setting a position in a file failed"},
    {ERROR_STATUS_CODE_106, "'endmacr' with extra text"},
    {ERROR_STATUS_CODE_107, "Failed to copy file during macros expansion"},
    {ERROR_STATUS_CODE_108, "Macros expansion in an .as file failed"},
    {ERROR_STATUS_CODE_109, "Illegal name for a macro"},
    {ERROR_STATUS_CODE_110, "Line is too long"},
    {ERROR_STATUS_CODE_111, "Macro has more than one definition"},
    {ERROR_STATUS_CODE_112, "Label is already used"},
    {ERROR_STATUS_CODE_113, "Op code %s not found"},
    {ERROR_STATUS_CODE_114, "Received too many arguments"}, /* TODO add "expected %s argument(s)" */
    {ERROR_STATUS_CODE_115, "Missing label name"},
    {ERROR_STATUS_CODE_116, "Ignoring label"},
    {ERROR_STATUS_CODE_117, "Argument must be a number but got: %s"},
    {ERROR_STATUS_CODE_118, "Invalid string, no closing and/or opening quote: %s"},
    {ERROR_STATUS_CODE_119, "Incorrect number of arguments, expected %d"},
};

/*
* Internal to this file's functions
Returns the error message associated with the given error code.
 */
char *get_error_message(int error_code)
{
    int i, errors_count = sizeof(errors) / sizeof(errors[0]);
    for (i = 0; i < errors_count; i++)
    {
        if (errors[i].error_code == error_code)
        {
            return errors[i].error_msg;
        }
    }
    return NULL;
}

void print_system_error(int error_code)
{
    printf("SYSTEM ERROR: CODE:%d | %s\n", error_code, get_error_message(error_code));
}

void print_file_error(int error_code, location_in_file file, ...)
{
    va_list args;
    va_start(args, file);

    printf("FILE ERROR: CODE:%d in %s at line:%d | there is an error: ", error_code, file.file_name, file.line_number);
    vprintf(get_error_message(error_code), args);
    printf("\n");

    va_end(args);
}

void print_file_warning(int error_code)
{
    printf("SYSTEM WARNING: CODE:%d | %s\n", error_code, get_error_message(error_code));
}
