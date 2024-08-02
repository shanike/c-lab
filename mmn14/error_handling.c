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
    {ERROR_STATUS_CODE_111, "Macro has more than one definition"}};

void print_system_error(int error_code)
{
    printf("SYSTEM ERROR: CODE:%d | %s\n", error_code, errors[error_code].error_msg);
}

void print_file_error(int error_code, location_in_file file)
{
    printf("FILE ERROR: CODE:%d in %s at line:%d | there is error: %s\n", error_code,
           file.file_name, file.line_number, errors[error_code].error_msg);
}
