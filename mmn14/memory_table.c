#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./memory_table.h"
#include "./generic_file_functions.h"
#include "./error_handling.h"
#include "./global_variables.h"

/* TODO merge with list_data_structure.c and labels_table.c */

wordNode *create_new_word_node(word value, int address)
{
    wordNode *node = allocate_memory_with_check(sizeof(wordNode));

    node->value = value;
    node->address = address;
    node->next = NULL;

    return node;
}

int add_node_to_list_word(wordNode **head, word value, int address)
{
    wordNode *new_node, *current, *node_exists;

    if (IS_DEBUG)
        printf("Adding word node\n");

    new_node = create_new_word_node(value, address);

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
    int i;
    for (i = 0; i < BITS_IN_WORD; i++)
    {
        if (i && i % 4 == 0)
        {
            printf(" ");
        }
        printf("%d", (num & (1 << i)) ? 1 : 0);
    }
}

void print_list_word(wordNode *head)
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
        printf("\n\t[(address: %d, value: ", current->address);
        print_bits(current->value);
        printf(")]");
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