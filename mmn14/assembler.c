#include <stdio.h>

#include "read_file.h"

int main(int argc, char *argv[])
{
    int i;
    if (argc < 2)
    {
        printf("Usage: assembler <file1> <file2> ...\n");
        return 1;
    }
    for (i = 1; i < argc; i++)
    {
        read_file(argv[i]);
    }
    return 0;
}