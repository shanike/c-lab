#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "global_variables.h"
#include "generic_file_functions.h"

#define SYSTEM_ERROR "SYSTEM ERROR (code %d) | %s\n"
#define FILE_ERROR_OPENING "FILE ERROR (code %d) in %s at line %d | there is an error: "
#define FILE_WARNING "FILE WARNING (code %d) | %s\n"

/* An error with an associated error code and error message */
typedef struct Error
{
    int error_code;  /* Unique code for the error */
    char *error_msg; /* Error message associated with the error */
} Error_t;

typedef enum ERROR_STATUS_CODES
{
    ERROR_STATUS_CODE_100, /* Allocate memory failure */
    ERROR_STATUS_CODE_101, /* Failed open file for writing */
    ERROR_STATUS_CODE_102, /* Failed open file for reading */
    ERROR_STATUS_CODE_103, /* Macro without name definition */
    ERROR_STATUS_CODE_104, /* Extra text after macro name definition*/
    ERROR_STATUS_CODE_105, /* Failed to set a position in a file */
    ERROR_STATUS_CODE_106, /* Extra text in "endmacr" line */
    ERROR_STATUS_CODE_107, /* Failed to copy file during macros expansion */
    ERROR_STATUS_CODE_108, /* Macros expansion in an .as file failed */
    ERROR_STATUS_CODE_109, /* Illegal name for macro */
    ERROR_STATUS_CODE_110, /* Line is too long */
    ERROR_STATUS_CODE_111, /* Macro has more than one definition */
    ERROR_STATUS_CODE_112, /* Label is already used */
    ERROR_STATUS_CODE_113, /* Op code %s not found */
    ERROR_STATUS_CODE_114, /* Received too many arguments, expected just 1 */
    ERROR_STATUS_CODE_115, /* Missing label name */
    ERROR_STATUS_CODE_116, /* Ignoring label */
    ERROR_STATUS_CODE_117, /* Argument must be a number but got: %s */
    ERROR_STATUS_CODE_118, /* Invalid string, no closing and/or opening quote: %s */
    ERROR_STATUS_CODE_119, /* Incorrect number of arguments, expected %d */
    ERROR_STATUS_CODE_120, /* An immediate addressing method must be a number, but got %s */
    ERROR_STATUS_CODE_121, /* Invalid register name: %s */
    ERROR_STATUS_CODE_122, /* Invalid label name: %s */
    ERROR_STATUS_CODE_123, /* Found label with the same name as one of the macros */
    ERROR_STATUS_CODE_124, /* Undefined label %s */
    ERROR_STATUS_CODE_125  /* Number value is out of range: %d. Should be between %d and %d */
} ERROR_STATUS_CODES;

/* Function declarations */

/**
 * Print a system error message to the standard output.
 *
 * @param error_code The error code for which the message should be printed.
 */
void print_system_error(int error_code);

/**
 * Print a system warning message to the standard output.
 *
 * @param error_code The error code for which the message should be printed.
 */
void print_file_warning(int error_code);

/**
 * Print a file-related error message to the standard output.
 * The error message may contain additional arguments, as specified in the errors array.
 *
 * @param error_code The error code for which the message should be printed.
 * @param file       The file location where the error occurred.
 * @param ...        Additional arguments to be printed in the error message.
 */
void print_file_error(int error_code, location_in_file file, ...);

/**
 * Print a file-related error message to the standard output.
 * The error message may contain additional arguments, as specified in the errors array.
 *
 * @param error_code The error code for which the message should be printed.
 * @param file       The file location where the error occurred.
 * @param args       Additional arguments to be printed in the error message, as a va_list.
 */
void print_file_error_args(int error_code, location_in_file file, va_list args);

#endif /* ERROR_HANDLING_H */
