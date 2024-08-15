#include <stdio.h>

#include "./validations.h"
#include "./generic_file_functions.h"
#include "./global_variables.h"
#include "./encoding.h"
#include "./memory_table.h"
#include "./error_handling.h"
#include "./addressing_methods.h"
#include "bitwise_functions.h"
#include "a_r_e_fields.h"

/* TODO temp */
void print_opcode(operation *op)
{
    printf("{ \n  name: %s,\n", op->name);
    printf("  arg_number: %d,\n", op->arg_number);
    printf("  code: %d,\n", op->code);
    printf("}\n");
}

/* TODO temp */
void print_array(char *name, char **array, int array_len)
{
    int i;
    printf("%s", name);
    for (i = 0; i < array_len; i++)
    {
        if (i)
        {
            printf(", ");
        }
        printf("%d:%s (l:%ld)", i, array[i], strlen(array[i]));
    }
    printf("\n");
}
/* TODO temp */
void print_array_ints(char *name, int array[], int array_len)
{
    int i;
    printf("%s", name);
    for (i = 0; i < array_len; i++)
    {
        if (i)
        {
            printf(", ");
        }
        printf("%d:%d ", i, array[i]);
    }
    printf("\n");
}

/* TODO temp */
void print_encoding(word encoding)
{
    printf("encoding: ");
    print_bits(encoding);
    printf("\nencoding in hex: %04X\n", encoding);
}

/*
Splits a string into an array of strings, using the delimiters ", \t".
Returns the number of strings in the array.
*/
int split_args(char *args_str, char *args[], int args_number)
{
    char delim[] = ", \t";
    char *token = strtok(args_str, delim);
    int i;
    for (i = 0; i < args_number; i++)
    {
        if (token == NULL)
        {
            break;
        }
        args[i] = token;
        token = strtok(NULL, delim);
    }
    return i;
}

/* Returns the addressing method's index in the word encoding. */
int get_arg_encoding_index(enum arg_index arg_index)
{
    if (arg_index == FIRST_ARG)
    {
        return 7;
    }
    else if (arg_index == SECOND_ARG)
    {
        return 3;
    }
    return -1;
}

int encode_op(word *op_word, operation *op, char **args, location_in_file file_location, int *IC, wordNode **memory_table)
{
    int args_number = op->arg_number;
    int arg_encoding_index;
    int i;
    enum addressing_methods curr_addressing_method;

    if (IS_DEBUG)
        printf("encoding operation %s\n", op->name);

    set_decimal_in_bits(op_word, op->code, 11, 14);

    if (args_number == 1) /* TODO try to join the two if statements */
    {
        curr_addressing_method = find_addressing_method(args[0], file_location);
        if (IS_DEBUG)
            printf("addressing_method of arg[0] %s: %d\n", args[0], curr_addressing_method);
        if (curr_addressing_method == INVALID)
        {
            return FAILURE;
        }
        arg_encoding_index = get_arg_encoding_index(SECOND_ARG);
        if (IS_DEBUG)
            printf("arg_encoding_index: %d\n", arg_encoding_index);
        set_bit(
            op_word,
            arg_encoding_index + curr_addressing_method,
            1);
    }
    else
    {
        /* args_number == 2 */
        for (i = 0; i < args_number; i++)
        {
            curr_addressing_method = find_addressing_method(args[i], file_location);
            if (IS_DEBUG)
                printf("addressing_method of arg[i] %s: %d\n", args[i], curr_addressing_method);
            if (curr_addressing_method == INVALID)
            {
                return FAILURE;
            }

            /* args_number is lte MAX_ARGS_NUMBER (=2), so arg_end_index and arg_encoding_index will not be -1 */
            arg_encoding_index = get_arg_encoding_index(i);
            set_bit(
                op_word,
                arg_encoding_index + curr_addressing_method,
                1);
        }
    }

    turn_on_a(op_word);

    return SUCCESS;
}

int is_register_addressing_method(enum addressing_methods addressing_method)
{
    return addressing_method == DIRECT_REGISTER || addressing_method == INDIRECT_REGISTER;
}

int get_register_number(char *register_str, enum addressing_methods addressing_method)
{
    int i = 0;
    while (register_str[i] != 'r') /* Skip to the first digit */
    {
        i++;
    }
    i++; /* Skip 'r' too */
    return atoi(register_str + i);
}

int encode_args(char **args, int args_number, labelNode *labels_list, wordNode **memory_table, int *IC, location_in_file file_location)
{
    enum addressing_methods curr_addressing_method, *args_address_methods;

    FeatureType label_feature;
    int i;
    int is_common_word;
    int arg1_register_value, arg2_register_value;

    word arg_words[2] = {0, 0};

    if (IS_DEBUG)
        print_array("encoding args: ", args, args_number);

    args_address_methods = allocate_memory_with_check(args_number * sizeof(enum addressing_methods));
    if (args_address_methods == NULL)
    {
        return FAILURE;
    }
    for (i = 0; i < args_number; i++)
    {
        *(args_address_methods + i) = find_addressing_method(args[i], file_location);
    }

    is_common_word = is_register_addressing_method(args_address_methods[0]) &&
                     is_register_addressing_method(args_address_methods[1]);
    if (IS_DEBUG)
        printf("is_common_word: %d\n", is_common_word);

    if (is_common_word) /* TODO extract to another function `encode_two_registers` (או כדומה) */
    {
        arg1_register_value = get_register_number(args[0], args_address_methods[0]);
        arg2_register_value = get_register_number(args[1], args_address_methods[1]);

        set_decimal_in_bits(&arg_words[0], arg1_register_value, 6, 8);
        set_decimal_in_bits(&arg_words[0], arg2_register_value, 3, 5);

        turn_on_a(&arg_words[0]);

        add_node_to_list_word(memory_table, arg_words[0], *IC, args[0]);
        (*IC)++;

        return SUCCESS;
    }

    /* If the instruction has a single argument, it is considered as the "second" argument. That's why the loop iterates in reverse order. */
    for (i = 0; i < args_number; i++) /* TODO split to functions, so loop is not so long */
    {
        if (IS_DEBUG)
            printf("encoding arg %s\n", args[i]);

        curr_addressing_method = find_addressing_method(args[i], file_location);
        if (IS_DEBUG)
            printf("addressing_method of arg %s: %d\n", args[i], curr_addressing_method);

        if (curr_addressing_method == IMMEDIATE)
        {
            set_decimal_in_bits(&arg_words[i], atoi(args[i] + 1), 3, 14);

            turn_on_a(&arg_words[i]);
        }
        else if (curr_addressing_method == DIRECT)
        {
            /* TODO on SECOND PASS. for now, ignore on first pass
            set_decimal_in_bits(arg_words[i], find_node_in_list_label(labels_list, args[i])->value, 3, 14);
            label_feature = find_node_in_list_label(labels_list, args[i])->feature_type;
            if (label_feature == EXTERNAL)
            {
                turn_on_e(arg_words[i]);
            }
            else
            {
                turn_on_r(arg_words[i]);
            }
            */
        }
        else if (is_register_addressing_method(curr_addressing_method))
        {
            int register_number = get_register_number(args[i], curr_addressing_method);
            if (i == SECOND_ARG || args_number == 1)
            {
                set_decimal_in_bits(&arg_words[i], register_number, 3, 5);
            }
            else
            {
                set_decimal_in_bits(&arg_words[i], register_number, 6, 8);
            }
            turn_on_a(&arg_words[i]);
        }
        else
        {
            continue;
        }
        add_node_to_list_word(memory_table, arg_words[i], *IC, args[i]);
        (*IC)++;
    }

    return SUCCESS;
}

/*
Returns the number of cells in memory the operation takes.
*/
int encode_instruction(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **memory_table, labelNode *labels_list)
{
    word op_word = 0;

    char **args;
    int args_number = op->arg_number;
    int i;
    int is_error = 0;

    if (IS_DEBUG)
        printf("encoding operation %s with args %s\n", op->name, args_str);

    /* TODO extract init+reset of args to another func */
    args = allocate_memory_with_check(args_number * sizeof(char *));
    if (args == NULL)
    {
        return FAILURE;
    }
    /* Reset args elements to NULL: */
    for (i = 0; i < args_number; i++)
    {
        *(args + i) = NULL;
    }

    if (args_number > MAX_ARGS_NUMBER || split_args(args_str, args, args_number) != args_number)
    {
        print_file_error(ERROR_STATUS_CODE_119, file_location, args_number);
        return FAILURE;
    }

    if (encode_op(&op_word, op, args, file_location, IC, memory_table) == FAILURE)
    {
        is_error = 1;
    }
    add_node_to_list_word(memory_table, op_word, *IC, op->name);
    (*IC)++;

    if (args_number)
    {
        if (encode_args(args, args_number, labels_list, memory_table, IC, file_location) == FAILURE)
        {
            is_error = 1;
        }
    }

    if (IS_DEBUG)
        print_list_word_octal(*memory_table);

    free(args);
    return is_error ? FAILURE : SUCCESS;
}
