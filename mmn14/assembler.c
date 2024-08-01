#include <stdio.h>

#include "pre_assembler.h"


int main(int argc, char *argv[])
{
    int i;
    if (argc < 2)
    {
        fprintf(stderr, "Error: No input file(s)\n");
        printf("Usage: assembler <file1> <file2> ...\n");
        return 1;
    }
    for (i = 1; i < argc; i++)
    {
        process_macros(argv[i]);
    }
    return 0;
}