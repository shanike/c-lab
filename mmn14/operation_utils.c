#include "operation_utils.h"

operation OPERATIONS[] = {
    {"mov", 2, 0},
    {"cmp", 2, 1},
    {"add", 2, 2},
    {"sub", 2, 3},
    {"lea", 2, 4},
    {"clr", 1, 5},
    {"not", 1, 6},
    {"inc", 1, 7},
    {"dec", 1, 8},
    {"jmp", 1, 9},
    {"bne", 1, 10},
    {"red", 1, 11},
    {"prn", 1, 12},
    {"jsr", 1, 13},
    {"rts", 0, 14},
    {"stop", 0, 15}};

int get_operation(char *str, operation *op)
{
    int i;
    for (i = 0; i < OPERATIONS_NUMBER; i++)
    {
        if (strcmp(OPERATIONS[i].name, str) == 0)
        {
            if (op != NULL)
            {
                op->name = allocate_memory_with_check(strlen(OPERATIONS[i].name) + 1);
                if (!op->name)
                {
                    return 0;
                }
                strcpy(op->name, OPERATIONS[i].name);
                op->arg_number = OPERATIONS[i].arg_number;
                op->code = OPERATIONS[i].code;
            }
            return 1;
        }
    }
    return 0;
}

void free_operation(operation *op)
{
    if (op)
    {
        soft_free_mem(op->name);
        soft_free_mem(op);
        op->name = NULL;
        op = NULL;
    }
}