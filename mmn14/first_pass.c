/* *BTW I got the phrase "first pass" from google translate and chatgpt */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./first_pass.h"
#include "./global_variables.h"
#include "./generic_file_functions.h"
#include "./labels_table.h"
#include "./validations.h"
#include "./text_functions.h"
#include "./error_handling.h"

int first_pass(char filename[])
{
    /* Data counter == מונה הנתונים */
    int DC = 0;
    /* Instructions counter == מונה ההוראות */
    int IC = 0;

    char line[MAX_LINE_LENGTH], *word;
    FILE *fp;
    int word_len = 0;
    int line_number = 0;

    labelNode *labels_list = NULL;
    char *current_label = NULL;
    int op_code_l = 0;

    int errors_cnt = 0;

    if (!open_file_for_reading(filename, &fp))
    {
        printf("Error: failed to open file for reading\n");
        return FAILURE;
    }
    printf("First pass for file: %s\n", filename);

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) /* Iteration per line */
    {
        line_number++;

        if (IS_DEBUG)
            printf("\n----line %d----\n", line_number);

        /* Reset */
        current_label = NULL;
        op_code_l = 0;
        word_len = 0;

        /* Remove the newline character */
        line[strlen(line) - 1] = '\0';
        if (IS_DEBUG)
            printf("line: %s\n", line);

        word = strtok(line, " ");

        if (word == NULL || word[0] == ';')
        {
            /* Skip empty lines and comments */
            continue;
        }

        if (is_label(word)) /* If the line is a label */
        {                   /* TODO try extracting to func */
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

        if (is_instruction(word)) /* TODO: rename to directive?? */
        {
            if (IS_DEBUG)
                printf("it's a directive line!\n");
            if (strcmp(word, DIRECTIVE_DATA) == 0 || strcmp(word, DIRECTIVE_STRING) == 0)
            {                      /* TODO try extracting to func */
                if (current_label) /* If label exists: add to the labels list */
                {
                    if (add_node_to_list_label(&labels_list, current_label, DATA, DC) == FAILURE)
                    {
                        errors_cnt++;
                        continue;
                    }
                };

                if (strcmp(word, DIRECTIVE_DATA) == 0)
                {
                    if (IS_DEBUG)
                        printf("it's .data! ");
                    while ((word = strtok(NULL, " ,\t")))
                    {
if (!is_data_number(word))                         /* Word must be a number */
                        {
                            print_file_error(ERROR_STATUS_CODE_117, curr_location, word);
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
                    word = strtok(NULL, " \t");
                    word[strlen(word) - 1] = '\0'; /* Remove the quote from end of string */
                    word++;                        /* Remove the quote from start of string */
                    word_len = strlen(word);
                    DC += word_len;
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
                    printf("TODO: warn ignoring label %s\n", current_label); /* TODO warning */
                }

                current_label = strtok(NULL, " \t"); /* TODO #define inline_whitespace " \t" */
                if (!current_label)
                {
                    printf("TODO: missing label name\n"); /* TODO error */
                    continue;
                }
                if (strcmp(word, DIRECTIVE_EXTERN) == 0)
                {
                    if (add_node_to_list_label(&labels_list, current_label, EXTERNAL, 0) == FAILURE)
                    {
                        errors_cnt++;
                        continue;
                    }
                }
                else /* is DIRECTIVE_ENTRY */
                {
                    if (add_node_to_list_label(&labels_list, current_label, CODE, IC + 100) == FAILURE)
                    {
                        errors_cnt++;
                        continue;
                    }
                }
                if ((word = strtok(NULL, " \t")))
                {
                    printf("TODO: too many arguments\n"); /* TODO error */
                    continue;
                }
            }
        }
        else if (is_opcode(word))
        {
            if (IS_DEBUG)
                printf("it's an opcode!\n");
            /* TODO calc L (=op_code_l) */
            if (current_label) /* If label exists: add to the labels list */
            {
                if (add_node_to_list_label(&labels_list, current_label, CODE, IC + 100) == FAILURE)
                {
                    errors_cnt++;
                    continue;
                }
            }
            IC += op_code_l;
        }
        else
        {
            printf("TODO: error opcode not found: %s\n", word); /* TODO error */
            continue;
        }

    } /* End of while */

    print_list_label(labels_list);
    fclose(fp);
    return SUCCESS;
}
