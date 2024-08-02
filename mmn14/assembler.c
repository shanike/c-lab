#include <stdio.h>

#include "pre_assembler.h"


int main(int argc, char *argv[])
{
    char *input_file;
    int result;

    if (argc != 2)
    {
        /* TODO what's .asm ?(?)*/
        fprintf(stderr, "Usage: %s <input_file.asm>\n", argv[0]);
        return 0;
    }

    input_file = argv[1];

    result = process_macros(input_file); 

    if (result == 1)
    {
        printf("Pre-assembly completed successfully.\n");
    }
    else
    {
        printf("Pre-assembly failed.\n");
    }

    return 1;

/*
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
*/
}
