#include "first_pass.h"

void handle_error_flag(int *is_error)
{
    *is_error = 1;
}

void handle_error_log(int error_code, location_in_file file_location, int *errors_cnt, ...)
{
    va_list args;
    va_start(args, errors_cnt);

    handle_error_flag(errors_cnt);
    print_file_error_args(error_code, file_location, args);

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

/* Validates a data argument and adds it to the data table */
void add_data_argument(char *data_arg, location_in_file curr_location, int *is_error, int *DC, wordNode **data_table)
{
    if (IS_DEBUG_FIRST_PASS)
        printf("Adding data arg %s\n", data_arg);

    /* Data arg must be a number */
    if (!is_whole_number(data_arg))
    {
        handle_error_log(ERROR_STATUS_CODE_117, curr_location, is_error, data_arg);
        return;
    }

    /* Number must be in range */
    if (!validate_immediate_number(data_arg, curr_location))
    {
        handle_error_flag(is_error);
        return;
    }

    /* Add the number to `data_table` */
    if (add_node_to_list_word(data_table, atoi(data_arg), *DC, data_arg) == FAILURE)
    {
        handle_error_flag(is_error);
    }
    /* Update the data counter */
    (*DC)++;
}

/*
Returns 1 if the string has consecutive commas, while ignoring spaces and tabs.
Returns 0 otherwise.
*/
int has_consecutive_commas(char *str)
{
    int i, searching_for_comma = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == SPACE || str[i] == TAB)
        {
            continue;
        }
        if (str[i] == COMMA && !searching_for_comma)
        {
            return 1;
        }
        if (str[i] == COMMA) /* && searching_for_comma */
        {
            searching_for_comma = 0;
        }
        else
        {
            searching_for_comma = 1;
        }
    }
    return 0;
}

/*
Validates a string argument and adds it to the data table
Returns SUCCESS if the string was added successfully, FAILURE if it's invalid.
*/
int add_string(char **word, char *word_arg, int *DC, wordNode **data_table, int *is_error, location_in_file curr_location)
{
    char *c;

    /* If no value ignore */
    if (!word_arg)
    {
        return SUCCESS;
    }

    /* Extract the string argument (=remove quotes) */
    if (extract_data_string(word_arg, word, curr_location) == FAILURE)
    {
        handle_error_flag(is_error);
        return FAILURE;
    }

    /* Add each char of .string argument to `data_table` in ascii form */
    c = *word;
    while (*c)
    {
        if (add_node_to_list_word(data_table, *c, *DC, c) == FAILURE)
        {
            handle_error_flag(is_error);
        }
        c++;
        (*DC)++;
    }

    /* And add a \0 at the end */
    if (add_node_to_list_word(data_table, '\0', *DC, "\\0") == FAILURE)
    {
        handle_error_flag(is_error);
    }
    (*DC)++;

    return SUCCESS;
}

/*
Validates an instruction, encodes it and adds it to the instructions table
*/
void handle_instruction(char *word, location_in_file curr_location, int *is_error, int *was_label_malloced, char *current_label, labelNode **labels_list, wordNode **instructions_table, int *IC)
{
    int encode_result,
        is_operation;

    operation *op = NULL;

    op = allocate_memory_with_check(sizeof(operation));
    op->name = NULL;

    is_operation = get_operation(word, op);

    if (is_operation == FAILURE || !op)
    {
        soft_free_operation(op);
        if (is_operation == FAILURE)
            handle_error_log(ERROR_STATUS_CODE_113, curr_location, is_error, word);
        return;
    }

    /* If label exists: add to the labels list */
    if (current_label)
    {
        if (add_node_to_labels_list(labels_list, current_label, CODE, *IC, curr_location) == FAILURE)
        {
            handle_error_flag(is_error);
        }
    }

    /* Encode and calc instruction length */
    encode_result = encode_instruction(op, strtok(NULL, ""), curr_location, IC, instructions_table, *labels_list);

    soft_free_operation(op);

    if (encode_result == FAILURE)
    {
        handle_error_flag(is_error);
    }
}

int ensure_memory_space(int IC, int DC, location_in_file location, int *is_error)
{
    if (IC + DC >= MEMORY_SIZE)
    {
        handle_error_log(ERROR_STATUS_CODE_126, location, is_error);
        return FAILURE;
    }
    return SUCCESS;
}

int first_pass(
    char filename[],
    labelNode **labels_list,
    wordNode **instructions_table,
    wordNode **data_table,
    int *IC,
    int *DC)
{
    char line[MAX_LINE_LENGTH],
        data_args[MAX_LINE_LENGTH],
        *word;
    FILE *fp;
    location_in_file curr_location;

    char *current_label = NULL;
    int was_label_malloced = 0;

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
        if (ensure_memory_space(*IC, *DC, curr_location, &is_error) == FAILURE)
        {
            break;
        }

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
                    if (add_node_to_labels_list(labels_list, current_label, DATA, *DC, curr_location) == FAILURE)
                    {
                        handle_error_flag(&is_error);
                    }
                };

                if (strcmp(word, DIRECTIVE_DATA) == 0)
                {
                    if (IS_DEBUG_FIRST_PASS)
                        printf("it's .data! ");
                    strcpy(data_args, strtok(NULL, ""));
                    if (has_consecutive_commas(data_args))
                    {
                        handle_error_log(ERROR_STATUS_CODE_127, curr_location, &is_error);
                        continue;
                    }
                    word = strtok(data_args, " ,\t");
                    while (word)
                    {
                        add_data_argument(word, curr_location, &is_error, DC, data_table);
                        word = strtok(NULL, " ,\t");
                    }
                }
                else if (strcmp(word, DIRECTIVE_STRING) == 0)
                {
                    if (IS_DEBUG_FIRST_PASS)
                        printf("it's .string!\n");

                    if (add_string(&word, strtok(NULL, ""), DC, data_table, &is_error, curr_location) == FAILURE)
                    {
                        continue;
                    }

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
                    if (add_node_to_labels_list(labels_list, current_label, EXTERNAL, 0, curr_location) == FAILURE)
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
            if (IS_DEBUG_FIRST_PASS)
                printf("it's an instruction!\n");

            handle_instruction(word, curr_location, &is_error, &was_label_malloced, current_label, labels_list, instructions_table, IC);
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
