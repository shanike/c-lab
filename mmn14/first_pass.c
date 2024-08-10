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

    if (!open_file_for_reading(filename, &fp))
    {
        printf("Error: failed to open file for reading\n");
        return FAILURE;
    }
    printf("First pass for file: %s\n", filename);

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        printf("\n----new line----\n");
        current_label = NULL;
                printf("line: %s\n", line);
        word = strtok(line, " ");
        printf("word: %s\n", word);

        if (word == NULL || word[0] == ';')
        {
            printf("ignoring\n");
            continue;
        }

        if (is_label(word)) /* If the line is a label */
        {
            printf("is label\n");
            word_len = strlen(word);
            /* Remove the ':' from the label */
            word[--word_len] = '\0';
            printf("label: %s\n", word);
            printf("label length: %d\n", word_len);
            /* Update current_label */
            current_label = malloc(word_len + 1);
            strcpy(current_label, word);
            current_label[word_len] = '\0';
            /* Set word to the next word for further processing */
            word = strtok(NULL, " ");
            printf("word: %s\n", word);
        }
        if (word[0] == '.')
        {
            printf("is directive line: %s\n", word);
            if (strcmp(word, DIRECTIVE_DATA) == 0 || strcmp(word, DIRECTIVE_STRING) == 0)
            {
                printf("is .data or .string\n");
                /* If label exists then add to the labels list */
                if (current_label && add_node_to_list_label(&labels_list, current_label, DATA, DC) == FAILURE)
                {
                    break;
                };

                if (strcmp(word, DIRECTIVE_DATA) == 0)
                {
                    printf(".data\n");
                    while ((word = strtok(NULL, " ,\t")))
                    {
                        printf("word: %s\n", word);
                        /* TODO add to data memory */
                        /* TODO check whether is_number validation is needed */
                        DC++;
                    }
                }
                else if (strcmp(word, DIRECTIVE_STRING) == 0)
                {
                                        word = strtok(NULL, " \t");
                    word[strlen(word) - 1] = '\0'; /* Remove the quote from end the string */
                    word++;                        /* Remove the quote from start of string */
                    word_len = strlen(word);
                    printf("word: %s\n", word);
                    /* TODO add to data memory */
                    DC += word_len;
                }
            }
        }
        else
        {
            printf("ignoring for now (%s)\n", word);
            /* TODO */
        }
    }

    print_list_label(labels_list);

    fclose(fp);
    return SUCCESS;
}
