#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "./validations.h"
#include "./global_variables.h"

op_code OP_CODES[] = {
    {"mov", 2, 0},
    {"cmp", 2, 1},
    {"add", 2, 2},
    {"sub", 2, 3},
    {"lea", 2, 4},
    {"not", 1, 5},
    {"clr", 1, 6},
    {"inc", 1, 7},
    {"dec", 1, 8},
    {"jmp", 1, 9},
    {"bne", 1, 10},
    {"red", 1, 11},
    {"prn", 1, 12},
    {"jsr", 1, 13},
    {"rts", 0, 14},
    {"stop", 0, 15}};
char *REGISTERS[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7"};

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

int is_opcode(char *str)
{
    int i;
    char *op_code_names[OP_CODES_NUMBER];
    for (i = 0; i < OP_CODES_NUMBER; i++)
    {
        op_code_names[i] = OP_CODES[i].name;
    }
    return is_one_of(str, op_code_names, OP_CODES_NUMBER);
}

/* TODO merge is_opcode with get_opcode */

int get_opcode(char *str, op_code *op)
{
    int i;
    for (i = 0; i < OP_CODES_NUMBER; i++)
    {
        if (strcmp(OP_CODES[i].name, str) == 0)
        {
            op->name = OP_CODES[i].name;
            op->arg_number = OP_CODES[i].arg_number;
            op->code = OP_CODES[i].code;
            return 1;
        }
    }
    return 0;
}

int is_register(char *str)
{
    return is_one_of(str, REGISTERS, REGISTERS_NUMBER);
}

int is_label(char *str)
{
    int i;

    /* A label must not be over 31 characters long */
    /* A label must start with an alphabetic character */
    /* A label's last character must be a colon */
    if (strlen(str) > MAX_LABEL_LENGTH || !isalpha(str[0]) || str[strlen(str) - 1] != ':')
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
    if (is_directive(str) || is_opcode(str) || is_register(str))
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