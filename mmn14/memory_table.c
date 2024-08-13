#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./memory_table.h"
#include "./generic_file_functions.h"
#include "./error_handling.h"
#include "./global_variables.h"

/* TODO merge with list_data_structure.c and labels_table.c */

wordNode *create_new_word_node(word value, int address, char *temp_name)
{
    wordNode *node = allocate_memory_with_check(sizeof(wordNode));

    node->value = value;
    node->address = address;
    if (temp_name)
        strcpy(node->temp_name, temp_name);
    node->next = NULL;

    return node;
}

int add_node_to_list_word(wordNode **head, word value, int address, char *temp_name)
{
    wordNode *new_node, *current, *node_exists;

    if (IS_DEBUG)
        printf("Adding word node\n");

    new_node = create_new_word_node(value, address, temp_name);

    /* If the list is empty, add the new node to the head of the list */
    if (*head == NULL)
    {
        *head = new_node;
    }

    /* If the list is not empty, add the new node down the list */
    else
    {
        /* Traverse to the end of the list */
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        /* Append the new node at the end of the list */
        current->next = new_node;
    }
    return SUCCESS;
}

/* TODO temp..? */
/* Prints the bits of a number, left to right. */
void print_bits(word num)
{
    int i, rtl_i;
    for (i = 0; i < BITS_IN_WORD; i++)
    {
        rtl_i = BITS_IN_WORD - 1 - i;
        if (i && i % 4 == 0)
        {
            printf(" ");
        }
        printf("%d", (num & (1 << rtl_i)) ? 1 : 0);
    }
}

void print_list_word_binary(wordNode *head)
{
    wordNode *current = head;
    int i = 0;
    printf("List: ");
    while (current != NULL)
    {
        if (i)
        {
            printf(" -> ");
        }
        printf("\n\t[(temp_name:%s, address: %d, value: ", current->temp_name, current->address);
        print_bits(current->value);
        printf(")]");
        current = current->next;
        i++;
    }
    printf("\n");
}

void print_list_word_octal(wordNode *head)
{
    wordNode *current = head;
    int i = 0;
    printf("List: ");
    while (current != NULL)
    {
        if (i)
        {
            printf(" -> ");
        }
        printf("\n\t[(temp_name:%s, address: %d, value: %05o)]", current->temp_name, current->address, current->value);
        current = current->next;
        i++;
    }
    printf("\n");
}

void free_node_word(wordNode *node1)
{
    free(node1);
}

void free_list_word(wordNode *head)
{
    /* Go through the linked list and free memory allocated fot each node in the list */
    while (head != NULL)
    {
        wordNode *temp = head;
        head = head->next;
        free_node_word(temp);
    }
}