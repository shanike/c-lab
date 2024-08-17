#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "second_pass.h"
#include "error_handling.h"
#include "generic_file_functions.h"
#include "global_variables.h"
#include "entries_output.h"
#include "ob_output.h"
#include "encoding.h"


int exec_second_pass(char *input_file_name, labelNode **labels_table, wordNode **instructions, wordNode **data, int IC, int DC)
{
    FILE *fp, *ext_fp;
    int is_error = 0;
    location_in_file curr_location;
    char line[MAX_LINE_LENGTH], *ext_file_name, *word;

    int second_pass_IC = INSTRUCTIONS_MEMORY_ADDRESS_START;

    char *curr_label_name = NULL;
    operation *curr_operation = NULL;

    if (!open_file_for_reading(input_file_name, &fp))
    {
        is_error = 1;
    }

    curr_location.line_number = 0;
    curr_location.file_name = input_file_name;

    /* Create the output file name with an '.ext' extension */
    ext_file_name = create_new_file_name(input_file_name, EXTERN_FILE_EXT);

    /* Open the new '.ext' file for writing */
    if (!open_file_for_writing(ext_file_name, &ext_fp))
    {
        fclose(ext_fp);
        is_error = 1;
    }

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        /* Remove the newline character, if exists */
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        if (IS_DEBUG_SECOND_PASS)
            printf("line: %s\n", line);

        word = strtok(line, " ");
        if (word == NULL)
        {
            continue;
        }

        if (is_label(word, 0))
        {
            /* Strip and ignore label */
            word = strtok(NULL, INLINE_WHITESPACE);
        }

        /* Update .entry labels to have a feature_type of ENTRY */
        if (strcmp(word, DIRECTIVE_ENTRY) == 0) /* An entry directive */
        {
            curr_label_name = strtok(NULL, INLINE_WHITESPACE);
            set_label_as_entry(labels_table, curr_label_name);
        }
        else if (is_directive(word))
        {
            /* Skip other directives */
            continue;
        }

        else /* Is an instruction line! */
        {
            /* Calc instruction length */

            if (curr_operation != NULL)
            {
                /* Free the prev operation */
                free(curr_operation);
            }
            curr_operation = allocate_memory_with_check(sizeof(curr_operation));
            if (!curr_operation)
            {
                return FAILURE;
            }

            get_operation(word, curr_operation);

            if (encode_labels(curr_operation, strtok(NULL, ""), curr_location, &second_pass_IC, instructions, *labels_table) == FAILURE)
            {
                is_error = 1;
                continue;
            }
        }
    }

    if (is_error == 1)
    {
        return FAILURE;
    }

    /* Create the outputs files ".ob" and ".ent" and write their data */
    create_ob_file(*instructions, *data, input_file_name, IC, DC);

    create_entries_output(*labels_table, input_file_name);

    fclose(fp);

    free(ext_file_name);
    free(curr_operation);

    return SUCCESS;
}
