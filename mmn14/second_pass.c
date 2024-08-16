#include <stdio.h>

#include "second_pass.h"
#include "error_handling.h"
#include "generic_file_functions.h"
#include "global_variables.h"
#include "entries_output.h"
#include "encoding.h"

int create_ob_file(wordNode *instructions, wordNode *data, char *input_file_name, int IC, int DC)
{
    int address, word_content;
    FILE *ob_fp;
    char *ob_file_name;

    /* Create the output file name with an '.ob' extension */
    ob_file_name = create_new_file_name(input_file_name, OBJECT_FILE_EXT);

    /* Open the new .ob file for writing */
    if (!open_file_for_writing(ob_file_name, &ob_fp))
    {
        fclose(ob_fp);
        return FAILURE;
    }

    /* Write the values of IC and DC in the first line of the ob file file */
    fprintf(ob_fp, "%d %d\n", IC, DC);

    /* Write each memory word (address and value) in the required format */

    while (instructions != NULL || data != NULL)
    {
        if (instructions != NULL)
        {
            address = instructions->address;
            word_content = instructions->value;
            instructions = instructions->next;
        }
        else
        {
            address = data->address;
            word_content = data->value;
            data = data->next;
        }

        /* Print address in 4-digit decimal format and content in 5-digit octal format */
        fprintf(ob_fp, "%04d %05o\n", address, word_content);
    }

    free(ob_file_name);
    fclose(ob_fp);

    return SUCCESS;
}

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

        /* TODO Check if this line uses a label */
        else /* is an instruction line! */
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

        /* TODO If so, replace each label usage in the table with the corresponding address in labels table */

        /* TODO For each extern type label , write it in the .ext file */
    }

    if (is_error == 1)
    {
        return FAILURE;
    }

    /* Create the outputs files ".ob" and ".ent" and write their data */
    create_ob_file(*instructions, *data, input_file_name, IC, DC);

    create_entries_output(*labels_table, input_file_name);

    /* TODO Free all the allocated memory and resources used during the second pass */

    fclose(fp);

    free(ext_file_name);
    free(curr_operation);

    return SUCCESS;
}
