#include "error_handling.h"

/* The Following array specifies the error status code numbers and the corresponding error message. */
Error_t errors[] = {
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
    {ERROR_STATUS_CODE_114, "Received too many arguments, expected just 1"},
    {ERROR_STATUS_CODE_115, "Missing label name"},
    {ERROR_STATUS_CODE_116, "Ignoring label"},
    {ERROR_STATUS_CODE_117, "Argument must be a number but got: %s"},
    {ERROR_STATUS_CODE_118, "Invalid string, no closing and/or opening quote: %s"},
    {ERROR_STATUS_CODE_119, "Incorrect number of arguments, expected %d"},
    {ERROR_STATUS_CODE_120, "An immediate addressing method must be a number, but got %s"},
    {ERROR_STATUS_CODE_121, "Invalid register name: %s"},
    {ERROR_STATUS_CODE_122, "Invalid label name: %s"},
    {ERROR_STATUS_CODE_123, "Found label with the same name as one of the macros"},
    {ERROR_STATUS_CODE_124, "Undefined label %s"},
    {ERROR_STATUS_CODE_125, "Number value %d is out of range, should be between %d and %d"},
    {ERROR_STATUS_CODE_126, "Memory reached its maximum capacity"},
    {ERROR_STATUS_CODE_127, "Invalid number of commas between numbers"}
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
    printf(SYSTEM_ERROR, error_code, get_error_message(error_code));
}

/* Internal function to print the constant start of a file error */
void print_file_error_start(int error_code, location_in_file file)
{
    printf(FILE_ERROR_OPENING, error_code, file.file_name, file.line_number);
}

void print_file_error_args(int error_code, location_in_file file, va_list args)
{
    print_file_error_start(error_code, file);
    vprintf(get_error_message(error_code), args);
    printf("\n");
}

void print_file_error(int error_code, location_in_file file, ...)
{
    va_list args;
    va_start(args, file);

    print_file_error_args(error_code, file, args);
    printf("\n");

    va_end(args);
}

void print_file_warning(int error_code)
{
    printf(FILE_WARNING, error_code, get_error_message(error_code));
}
