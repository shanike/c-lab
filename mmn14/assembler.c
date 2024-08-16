#include <stdio.h>
#include <string.h>

#include "pre_assembler.h"
#include "./first_pass.h"
#include "second_pass.h"
#include "./generic_file_functions.h"

int main(int argc, char *argv[])
{
    int i, result;
    char *input_filename, *am_filename;

    labelNode *labels_list = NULL;
    wordNode *instructions_table = NULL;
    wordNode *data_table = NULL;

    int IC = 0, DC = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        input_filename = argv[i];

        printf("Processing file: %s\n", input_filename);

        result = process_macros(create_new_file(input_filename, ASSEMBLY_FILE_EXT));

        if (result == FAILURE)
        {
            fprintf(stderr, "Pre-assembly failed for file: %s\n", input_filename);
            continue;
        }

        am_filename = create_new_file(input_filename, AFTER_MACRO_FILE_EXT);
        printf("AM file: %s\n", am_filename);

        result = first_pass(
            am_filename,
            &labels_list,
            &instructions_table,
            &data_table,
            &IC,
            &DC);

        if (result == FAILURE)
        {
            fprintf(stderr, "First pass failed for file: %s\n", input_filename);
            continue;
        }

        result = exec_second_pass(
            am_filename,
            &labels_list,
            &instructions_table,
            &data_table,
            IC,
            DC);
    }

    return 0;
}
