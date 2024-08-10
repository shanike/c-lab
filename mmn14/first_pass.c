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

int first_pass(char filename[])
{
    /* Data counter == מונה הנתונים */
    int DC = 0;
    /* Instructions counter == מונה ההוראות */
    int IC = 0;

    char line[MAX_LINE_LENGTH], *word;
    FILE *fp;
    int word_len = 0;

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
        printf("\n----new line----\n");
        current_label = NULL;
        line[strlen(line) - 1] = '\0'; /* Remove the newline character */
        printf("line: %s\n", line);
        word = strtok(line, " ");

        if (word == NULL || word[0] == ';')
        {
            printf("ignoring\n");
            continue;
        }

        if (is_label(word)) /* If the line is a label */
        {                   /* TODO try extracting to func */
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
                    printf("it's .data! ");
                    while ((word = strtok(NULL, " ,\t")))
                    {
                        /* TODO check whether is_number validation is needed */
                        DC++;
                    }
                    printf("setting DC to %d\n", DC);
                }
                else if (strcmp(word, DIRECTIVE_STRING) == 0)
                {
                    printf("it's .string! ");
                    word = strtok(NULL, " \t");
                    word[strlen(word) - 1] = '\0'; /* Remove the quote from end of string */
                    word++;                        /* Remove the quote from start of string */
                    word_len = strlen(word);
                    DC += word_len;
                    printf("setting DC to %d\n", DC);
                }
            }
            else if (strcmp(word, DIRECTIVE_EXTERN) == 0 || strcmp(word, DIRECTIVE_ENTRY) == 0)
            {
                printf("it's .extern or .entry!\n");
                if (current_label)
                {
                    printf("TODO: warn ignoring label %s\n", current_label); /* TODO warning */
                }

                current_label = strtok(NULL, " \t"); /* TODO #define inline_whitespace " \t" */
                printf("current_label: %s\n", current_label);
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
            printf("it's an opcode!\n");
            /* TODO calc L (=op_code_l) */
            if (current_label) /* If label exists: add to the labels list */
            {
                if (add_node_to_list_label(&labels_list, current_label, CODE, IC) == FAILURE)
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
