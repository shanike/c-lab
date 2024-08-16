#include <stdio.h>
#include <string.h>

#include "pre_assembler.h"
#include "./first_pass.h"
#include "./generic_file_functions.h"

int main(int argc, char *argv[])
{
    int i;
    char *input_file;
    int result;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        input_file = argv[i];

        printf("Processing file: %s\n", input_file);

        result = process_macros(create_new_file_name(input_file, ASSEMBLY_FILE_EXT));

        if (!result)
        {
            fprintf(stderr, "Pre-assembly failed for file: %s\n", input_file);
        }
    
        result = first_pass(create_new_file_name(input_file, AFTER_MACRO_FILE_EXT));

        if (result)
        {
            fprintf(stderr, "First pass failed for file: %s\n", input_file);
        }
    }

    return 0;
}
