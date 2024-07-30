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

int is_instruction(char *str)
{
    int i;

    if (str == NULL)
        return 0;

    /* Iterate through the instructions list and compare the given string with each instruction in the list */
    for (i = 0; i < INSTRUCTIONS_NUMBER; i++)
    {
        /* The string matches one of the instructions */
        if (strcmp(str, INSTRUCTIONS[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_opcode(char *str)
{
    int i;

    if (str == NULL)
        return 0;

    /* Iterate through the opcodes list and compare the string with each opcode in the list */
    for (i = 0; i < OP_CODES_NUMBER; i++)
    {
        if (strcmp(str, OP_CODES[i].opcode) == 0)
        {
            /* The string matches one of the opcodes */
            return 1;
        }
    }
    return 0;
}

int is_register(char *str)
{
    int i;

    if (str == NULL)
        return 0;

    /* Iterate through the registers list and compare the string with each register in the list */
    for (i = 0; i < REGISTERS_NUMBER; i++)
    {
        if (strcmp(str, REGISTERS[i]) == 0)
        {
            /* The string matches one of the registers */
            return 1;
        }
    }
    return -0;
}
