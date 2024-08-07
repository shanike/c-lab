#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "./validations.h"
#include "./global_variables.h"

op_code OP_CODES[] = {
    {"mov", 2},
    {"cmp", 2},
    {"add", 2},
    {"sub", 2},
    {"lea", 2},
    {"not", 1},
    {"clr", 1},
    {"inc", 1},
    {"dec", 1},
    {"jmp", 1},
    {"bne", 1},
    {"red", 1},
    {"prn", 1},
    {"jsr", 1},
    {"rts", 0},
    {"stop", 0}};
char *REGISTERS[] = {"@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7"};

char *INSTRUCTIONS[] = {".data", ".string", ".extern", ".entry"};

int is_one_of(char *str_input, char *array[], int array_length)
{
    int i;

    if (str_input == NULL)
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

int is_instruction(char *str)
{
    return is_one_of(str, INSTRUCTIONS, INSTRUCTIONS_NUMBER);
}

int is_opcode(char *str)
{
    int i;
    char *op_code_names[OP_CODES_NUMBER];
    for (i = 0; i < OP_CODES_NUMBER; i++)
    {
        op_code_names[i] = OP_CODES[i].opcode;
    }
    return is_one_of(str, op_code_names, OP_CODES_NUMBER);
}

int is_register(char *str)
{
    return is_one_of(str, REGISTERS, REGISTERS_NUMBER);
}

int is_label(char *str)
{
    /* A label must not be over 31 characters long */
    /* A label must start with an alphabetic character */
    /* A label's last character must be a colon */
    if (strlen(str) > MAX_LABEL_LENGTH || !isalpha(str[0]) || str[strlen(str) - 1] != ':')
    {
        return 0;
    }
    /* A label must not be a preserved word */
    if (is_instruction(str) || is_opcode(str) || is_register(str))
    {
        return 0;
    }
    return 1;
}