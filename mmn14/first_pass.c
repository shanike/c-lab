/* *BTW I got the phrase "first pass" from google translate and chatgpt */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "./first_pass.h"
#include "./global_variables.h"
#include "./generic_file_functions.h"
#include "./labels_table.h"
#include "./validations.h"
#include "./text_functions.h"
#include "./error_handling.h"
#include "./encoding.h"

void handle_error_cnt(int *errors_cnt)
{
    *errors_cnt += 1;
}

void handle_error_log(int error_code, location_in_file file_location, int *errors_cnt, ...)
{
    va_list args;
    va_start(args, errors_cnt);

    handle_error_cnt(errors_cnt);
    print_file_error(error_code, file_location, args);

    va_end(args);
}

/*
Returns the number of errors that occurred during the first pass.
*/
int first_pass(char filename[])
{
    /* Data counter == מונה הנתונים */
    int DC = 0;
    /* Instructions counter == מונה ההוראות */
    int IC = 0;

    char line[MAX_LINE_LENGTH], *word;
    FILE *fp;
    int word_len = 0;
    location_in_file curr_location;

    labelNode *labels_list = NULL;
    char *current_label = NULL;
    int op_code_l = 0;
    op_code *operation = NULL;

    int errors_cnt = 0;

    if (!open_file_for_reading(filename, &fp))
    {
        handle_error_cnt(&errors_cnt);
    }

    curr_location.line_number = 0;
    curr_location.file_name = filename;

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) /* Iteration per line */
    {
        curr_location.line_number++;

        if (IS_DEBUG)
            printf("\n----line %d----\n", curr_location.line_number);

        /* Reset */
        current_label = NULL;
        op_code_l = 0;
        word_len = 0;

        /* Remove the newline character */
        line[strlen(line) - 1] = '\0';
        if (IS_DEBUG)
            printf("line: %s\n", line);

        word = strtok(line, " ");

        if (!word || word[0] == ';')
        {
            /* Skip empty lines and comments */
            continue;
        }

        if (is_label(word)) /* If the line is a label */
        {
            if (IS_DEBUG)
                printf("it's a label! saving name.\n");
            word_len = strlen(word);
            /* Remove the ':' from the label */
            word[--word_len] = '\0';
            /* Update current_label */
            current_label = malloc(word_len + 1);
            strcpy(current_label, word);
            current_label[word_len] = '\0';
            /* Set word to the next word for further processing */
            word = strtok(NULL, " ");
        }

        if (is_directive(word))
        {
            if (IS_DEBUG)
                printf("it's a directive line!\n");
            if (strcmp(word, DIRECTIVE_DATA) == 0 || strcmp(word, DIRECTIVE_STRING) == 0)
            {
                if (current_label) /* If label exists: add to the labels list */
                {
                    if (add_node_to_list_label(&labels_list, current_label, DATA, DC, curr_location) == FAILURE)
                    {
                        handle_error_cnt(&errors_cnt);
                    }
                };

                if (strcmp(word, DIRECTIVE_DATA) == 0)
                {
                    if (IS_DEBUG)
                        printf("it's .data! ");
                    while ((word = strtok(NULL, " ,\t")))
                    {
                        if (!is_data_number(word)) /* Word must be a number */
                        {
                            handle_error_log(ERROR_STATUS_CODE_117, curr_location, &errors_cnt, word);
                        }
                        else
                        {
                            DC++;
                        }
                    }
                    if (IS_DEBUG)
                        printf("setting DC to %d\n", DC);
                }
                else if (strcmp(word, DIRECTIVE_STRING) == 0)
                {
                    if (IS_DEBUG)
                        printf("it's .string! ");
                    if (extract_data_string(strtok(NULL, ""), &word, curr_location) == FAILURE)
                    {
                        handle_error_cnt(&errors_cnt);
                    }
                    DC += strlen(word) + 1; /* +1 for the '\0' */
                    if (IS_DEBUG)
                        printf("setting DC to %d\n", DC);
                }
            }
            else if (strcmp(word, DIRECTIVE_EXTERN) == 0 || strcmp(word, DIRECTIVE_ENTRY) == 0)
            {
                if (IS_DEBUG)
                    printf("it's .extern or .entry!\n");
                if (current_label)
                {
                    print_file_warning(ERROR_STATUS_CODE_116);
                }

                current_label = strtok(NULL, INLINE_WHITESPACE);
                if (!current_label)
                {
                    handle_error_log(ERROR_STATUS_CODE_115, curr_location, &errors_cnt);
                    continue;
                }
                if (strcmp(word, DIRECTIVE_EXTERN) == 0)
                {
                    if (add_node_to_list_label(&labels_list, current_label, EXTERNAL, 0, curr_location) == FAILURE)
                    {
                        handle_error_cnt(&errors_cnt);
                    }
                }
                else /* is DIRECTIVE_ENTRY */
                {
                    if (add_node_to_list_label(&labels_list, current_label, CODE, IC + 100, curr_location) == FAILURE)
                    {
                        handle_error_cnt(&errors_cnt);
                    }
                }
                if ((word = strtok(NULL, INLINE_WHITESPACE)))
                {
                    handle_error_log(ERROR_STATUS_CODE_114, curr_location, &errors_cnt);
                }
            }
        }
        else if (is_opcode(word))
        {
            if (IS_DEBUG)
                printf("it's an opcode!\n");
            if (current_label) /* If label exists: add to the labels list */
            {
                if (add_node_to_list_label(&labels_list, current_label, CODE, IC + 100, curr_location) == FAILURE)
                {
                    handle_error_cnt(&errors_cnt);
                }
            }
            /* Calc operation length */
            if (operation != NULL)
            {
                /* Free the prev operation */
                free(operation);
            }
            operation = malloc(sizeof(operation));
            if (!get_opcode(word, operation))
            {
                handle_error_log(ERROR_STATUS_CODE_113, curr_location, &errors_cnt, word);
            }
            op_code_l = encode(operation, strtok(NULL, ""));
            IC += op_code_l;
        }
        else
        {
            handle_error_log(ERROR_STATUS_CODE_113, curr_location, &errors_cnt, word);
        }

    } /* End of while */

    print_list_label(labels_list);
    fclose(fp);
    return errors_cnt;
}
