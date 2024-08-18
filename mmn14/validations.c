#include "validations.h"

char *REGISTERS[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

char *DIRECTIVES[] = {DIRECTIVE_DATA, DIRECTIVE_STRING, DIRECTIVE_EXTERN, DIRECTIVE_ENTRY};

int is_one_of(char *str_input, char *array[], int array_length)
{
    int i;

    if (!str_input)
        return 0;

    /* Iterate through the instructions list and compare the given string with each instruction in the list */
    for (i = 0; i < array_length; i++)
    {
        /* The string matches one of the instructions */
        if (strcmp(str_input, array[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_directive(char *str)
{
    return is_one_of(str, DIRECTIVES, DIRECTIVES_NUMBER);
}

int is_register(char *str)
{
    return is_one_of(str, REGISTERS, REGISTERS_NUMBER);
}

int is_label(char *str, int is_colon_trimmed)
{
    int i;

    /* A label's last character must be a colon */
    if (!is_colon_trimmed && str[strlen(str) - 1] != COLON)
    {
        return 0;
    }

    /* A label must not be over 31 characters long */
    /* A label must start with an alphabetic character */
    if (strlen(str) > MAX_LABEL_LENGTH || !isalpha(str[0]))
    {
        return 0;
    }

    /* A label must contain only alphanumeric characters */
    for (i = 1; i < strlen(str) - 1; i++)
    {
        if (!isalnum(str[i]))
        {
            return 0;
        }
    }
    /* A label must not be a preserved word */
    if (is_directive(str) || get_operation(str, NULL) || is_register(str))
    {
        return 0;
    }
    return 1;
}

int is_whole_number(char *str)
{
    /* A number can be any whole number */
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+')
        {
            return 0;
        }
    }
    return 1;
}

int validate_immediate_number(char *str, location_in_file file_location)
{
    int num = atoi(str);
    if (num > (MAX_IMMEDIATE_VALUE) || num < (MIN_IMMEDIATE_VALUE))
    {
        print_file_error(ERROR_STATUS_CODE_125, file_location, num, MIN_IMMEDIATE_VALUE, MAX_IMMEDIATE_VALUE);
        return 0;
    }
    return 1;
}
