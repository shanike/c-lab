#include "second_pass.h"

int exec_second_pass(char *input_file_name, labelNode **labels_table, wordNode **instructions, wordNode **data, int IC, int DC)
{
    FILE *input_fp;
    int is_error = 0;
    location_in_file curr_location;
    char line[MAX_LINE_LENGTH], *word;

    int second_pass_IC = INSTRUCTIONS_MEMORY_ADDRESS_START;

    char *curr_label_name = NULL;
    operation *curr_operation = NULL;
    int encode_result = 0;

    labelNode *externals = NULL;

    if (!open_file_for_reading(input_file_name, &input_fp))
    {
        is_error = 1;
    }

    curr_location.line_number = 0;
    curr_location.file_name = input_file_name;

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, input_fp) != NULL)
    {

        /* Reset */
        curr_location.line_number++;
        curr_label_name = NULL;

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
            if (IS_DEBUG_SECOND_PASS)
                printf("it's .entry!\n");
            curr_label_name = strtok(NULL, INLINE_WHITESPACE);
            if (set_label_as_entry(labels_table, curr_label_name) == FAILURE)
            {
                print_file_error(ERROR_STATUS_CODE_124, curr_location);
                is_error = 1;
            }
        }
        else if (is_directive(word))
        {
            /* Skip other directives */
            continue;
        }

        else /* Is an instruction line! */
        {
            /* Calc instruction length */
            curr_operation = allocate_memory_with_check(sizeof(operation));
            if (!curr_operation)
            {
                return FAILURE;
            }

            get_operation(word, curr_operation);
            encode_result = encode_labels(
                curr_operation, strtok(NULL, ""), curr_location, &second_pass_IC, instructions, *labels_table, &externals);
            soft_free_operation(curr_operation);
            if (encode_result == FAILURE)
            {
                is_error = 1;
                continue;
            }
        }
    }
    fclose(input_fp);

    if (is_error == 1)
    {
        return FAILURE;
    }

    /* Create the output files and write their data */

    create_ob_file(*instructions, *data, input_file_name, IC, DC);

    create_entries_file(*labels_table, input_file_name);

    create_externals_file(externals, input_file_name);

    return SUCCESS;
}
