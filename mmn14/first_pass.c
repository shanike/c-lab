#include "first_pass.h"

void handle_error_flag(int *is_error)
{
    *is_error = 1;
}

/* TODO check! does this work for strings? for ints? */
void handle_error_log(int error_code, location_in_file file_location, int *errors_cnt, ...)
{
    va_list args;
    va_start(args, errors_cnt);

    handle_error_flag(errors_cnt);
    print_file_error(error_code, file_location, args);

    va_end(args);
}

void inc_data_table_addresses(wordNode *data_table, int IC)
{
    wordNode *curr = data_table;
    while (curr)
    {
        curr->address += IC;
        curr = curr->next;
    }
}

void inc_data_labels_addresses(labelNode *labels_list, int IC)
{
    labelNode *curr = labels_list;
    while (curr)
    {
        if (curr->feature_type == DATA)
        {
            curr->value += IC;
        }
        curr = curr->next;
    }
}

/* Removes the ':' from the label and saves it in current_label. */
void clean_and_save_label(char *word, char **current_label, int *was_label_malloced)
{
    int word_len = strlen(word);

    /* Remove the ':' from the label */
    word[--word_len] = '\0';

    /* Update current_label */
    *current_label = allocate_memory_with_check(word_len + 1);
    if (!(*current_label))
    {
        return;
    }
    *was_label_malloced = 1;
    strcpy(*current_label, word);
    (*current_label)[word_len] = '\0';
}

int first_pass(
    char filename[],
    labelNode **labels_list,
    wordNode **instructions_table,
    wordNode **data_table,
    int *IC,
    int *DC)
{
    char line[MAX_LINE_LENGTH], *word, *c;
    FILE *fp;
    location_in_file curr_location;

    char *current_label = NULL;
    int was_label_malloced = 0;
    operation *curr_op = NULL;
    int encode_result = 0;

    int is_error = 0;

    /* Data counter == מונה הנתונים */
    *DC = INSTRUCTIONS_MEMORY_ADDRESS_START;
    /* Instructions counter == מונה ההוראות */
    *IC = INSTRUCTIONS_MEMORY_ADDRESS_START;

    if (!open_file_for_reading(filename, &fp))
    {
        handle_error_flag(&is_error);
    }

    curr_location.line_number = 0;
    curr_location.file_name = filename;

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) /* Iteration per line */
    {
        curr_location.line_number++;

        if (IS_DEBUG_FIRST_PASS)
            printf("\n----line %d----\n", curr_location.line_number);

        /* Reset */
        if (was_label_malloced)
            soft_free_mem(current_label);
        current_label = NULL;
        was_label_malloced = 0;

        /* Remove the newline character, if exists */
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        if (IS_DEBUG_FIRST_PASS)
            printf("line: %s\n", line);

        word = strtok(line, " ");

        if (!word || word[0] == ';')
        {
            /* Skip empty lines and comments */
            if (IS_DEBUG_FIRST_PASS)
                printf("skipping empty line or comment\n");
            continue;
        }

        if (is_label(word, 0)) /* If the line is a label */
        {
            if (IS_DEBUG_FIRST_PASS)
                printf("it's a label! saving name.\n");
            clean_and_save_label(word, &current_label, &was_label_malloced);
            /* Set word to the next word for further processing */
            word = strtok(NULL, " ");
        }

        if (is_directive(word))
        {
            if (IS_DEBUG_FIRST_PASS)
                printf("it's a directive line!\n");
            if (strcmp(word, DIRECTIVE_DATA) == 0 || strcmp(word, DIRECTIVE_STRING) == 0)
            {
                if (current_label) /* If label exists: add to the labels list */
                {
                    if (add_node_to_list_label(labels_list, current_label, DATA, *DC, curr_location) == FAILURE)
                    {
                        handle_error_flag(&is_error);
                    }
                };

                if (strcmp(word, DIRECTIVE_DATA) == 0)
                {
                    if (IS_DEBUG_FIRST_PASS)
                        printf("it's .data! ");
                    while ((word = strtok(NULL, " ,\t")))
                    {
                        if (!is_whole_number(word)) /* Word must be a number */
                        {
                            handle_error_log(ERROR_STATUS_CODE_117, curr_location, &is_error, word);
                        }
                        else if (!validate_immediate_number(word, curr_location)) /* Number must be in range */
                        {
                            handle_error_flag(&is_error);
                        }
                        else
                        {
                            /* Add the number to `data_table` */
                            if (add_node_to_list_word(data_table, atoi(word), *DC, word) == FAILURE)
                            {
                                handle_error_flag(&is_error);
                            }
                            /* Update the data counter */
                            (*DC)++;
                        }
                    }
                    if (IS_DEBUG_FIRST_PASS)
                        printf("setting DC to %d\n", *DC);
                }
                else if (strcmp(word, DIRECTIVE_STRING) == 0)
                {
                    if (IS_DEBUG_FIRST_PASS)
                        printf("it's .string!\n");
                    /* TODO: maybe store the result of extract_data_string in a diff variable. */
                    if (extract_data_string(strtok(NULL, ""), &word, curr_location) == FAILURE)
                    {
                        handle_error_flag(&is_error);
                        continue;
                    }
                    /* Add each char of .string value to `data_table` in ascii form */
                    c = word;
                    while (*c)
                    {
                        if (add_node_to_list_word(data_table, *c, *DC, c) == FAILURE)
                        {
                            handle_error_flag(&is_error);
                        }
                        c++;
                        (*DC)++;
                    }
                    /* And add a \0 at the end */
                    if (add_node_to_list_word(data_table, '\0', *DC, "\\0") == FAILURE)
                    {
                        handle_error_flag(&is_error);
                    }
                    (*DC)++;

                    if (IS_DEBUG_FIRST_PASS)
                        printf("setting DC to %d\n", *DC);
                }
            }
            else if (strcmp(word, DIRECTIVE_EXTERN) == 0 || strcmp(word, DIRECTIVE_ENTRY) == 0)
            {
                if (IS_DEBUG_FIRST_PASS)
                    printf("it's .extern or .entry!\n");
                if (current_label)
                {
                    print_file_warning(ERROR_STATUS_CODE_116);
                }

                current_label = strtok(NULL, INLINE_WHITESPACE);
                was_label_malloced = 0;
                if (!current_label)
                {
                    handle_error_log(ERROR_STATUS_CODE_115, curr_location, &is_error);
                    continue;
                }
                if (strcmp(word, DIRECTIVE_EXTERN) == 0)
                {
                    if (!is_label(current_label, 1))
                    {
                        handle_error_log(ERROR_STATUS_CODE_122, curr_location, &is_error, current_label);
                        continue;
                    }
                    if (add_node_to_list_label(labels_list, current_label, EXTERNAL, 0, curr_location) == FAILURE)
                    {
                        handle_error_flag(&is_error);
                        continue;
                    }
                }
                else if ((word = strtok(NULL, INLINE_WHITESPACE)))
                {
                    handle_error_log(ERROR_STATUS_CODE_114, curr_location, &is_error);
                    continue;
                }
            }
        }
        else
        {
            curr_op = allocate_memory_with_check(sizeof(operation));
            if (get_operation(word, curr_op))
            {
                if (IS_DEBUG_FIRST_PASS)
                    printf("it's an operation!\n");

                if (!curr_op) /* Due to malloc failure */
                {
                    if (was_label_malloced)
                        soft_free_mem(current_label);
                    soft_free_operation(curr_op);
                    return FAILURE;
                }
                /* If label exists: add to the labels list */
                if (current_label)
                {
                    if (add_node_to_list_label(labels_list, current_label, CODE, *IC, curr_location) == FAILURE)
                    {
                        handle_error_flag(&is_error);
                    }
                }
                /* Calc instruction length */
                encode_result = encode_instruction(curr_op, strtok(NULL, ""), curr_location, IC, instructions_table, *labels_list);
                soft_free_operation(curr_op);
                if (encode_result == FAILURE)
                {
                    handle_error_flag(&is_error);
                    continue;
                }
            }
            else
            {
                printf("Error: unknown operation: %s\n", word);
                handle_error_log(ERROR_STATUS_CODE_113, curr_location, &is_error, word);
            }
        }

    } /* End of while */

    /* Reset IC and DC to clean counters without INSTRUCTIONS_MEMORY_ADDRESS_START */
    *IC -= INSTRUCTIONS_MEMORY_ADDRESS_START;
    *DC -= INSTRUCTIONS_MEMORY_ADDRESS_START;

    /* Update addresses of data_table to be after addresses of instructions_table */
    inc_data_table_addresses(*data_table, *IC);
    /* Update addresses of data labels themselves too to +instructions_length+INSTRUCTIONS_MEMORY_ADDRESS_START */
    inc_data_labels_addresses(*labels_list, *IC);

    if (was_label_malloced)
        soft_free_mem(current_label);

    fclose(fp);

    return is_error ? FAILURE : SUCCESS;
}
