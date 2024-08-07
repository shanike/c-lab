#include <stdio.h>
#include <string.h>

#include "pre_assembler.h"
#include "./first_pass.h"
#include "./generic_file_functions.h"

int temp_first_pass(char input_filename[])
{
    char *am_filename = create_new_file(input_filename, ".am");
    printf("TEMP - Calling first_pass with .am (=after pre-assembler) file: %s\n", am_filename);
    if(first_pass(am_filename)==FAILURE)
    {
        fprintf(stderr, "Error: first pass failed for file: %s\n", am_filename);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int result;
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 0;
    }

    for (i = 1; i < argc; i++)
    {
        char *input_file = argv[i];

        printf("Processing file: %s\n", input_file);
        return temp_first_pass(input_file); /* TODO remove this line and the temp function*/
        result = process_macros(create_new_file(input_file, ".as"));

        if (result == 1)
        {
            printf("Pre-assembly completed successfully for file: %s\n", input_file);
        }
        else
        {
            fprintf(stderr, "Pre-assembly failed for file: %s\n", input_file);
        }
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
