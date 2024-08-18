#include <stdio.h>
#include <string.h>

#include "pre_assembler.h"
#include "first_pass.h"
#include "second_pass.h"

#include "generic_file_functions.h"

int main(int argc, char *argv[])
{
    int i, result;
    char *input_filename, *as_filename, *am_filename;

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

        as_filename = create_new_file_name(input_filename, ASSEMBLY_FILE_EXT);
        result = pre_assembler(as_filename);

        if (result == FAILURE)
        {
            printf("Pre-assembly failed for file: %s\n", input_filename);
            continue;
        }

        am_filename = create_new_file_name(input_filename, AFTER_MACRO_FILE_EXT);

        result = first_pass(
            am_filename,
            &labels_list,
            &instructions_table,
            &data_table,
            &IC,
            &DC);

        if (result == FAILURE)
        {
            printf("First pass failed for file: %s\n", input_filename);
            continue;
        }

        if (IS_DEBUG)
            printf("\n\nFIRST PASS FINISHED ------------------------------------\n\n\n");

        result = exec_second_pass(
            am_filename,
            &labels_list,
            &instructions_table,
            &data_table,
            IC,
            DC);

        if (result == FAILURE)
        {
            printf("Second pass failed for file: %s\n", input_filename);
            continue;
        }

        printf("File %s was successfully assembled\n", input_filename);

        /* Clear and reset */
        free_list_label(labels_list);
        labels_list = NULL;

        free_list_word(instructions_table);
        instructions_table = NULL;

        free_list_word(data_table);
        data_table = NULL;

        free(as_filename);
        free(am_filename);
    }

    return 0;
}
