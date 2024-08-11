#include <stdio.h>

#include "./validations.h"

void print_opcode(op_code *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
}

int encode(op_code *operation, char *args_str)
{
    print_opcode(operation);
    printf("Arguments: %s\n", args_str);
    return 0;
}