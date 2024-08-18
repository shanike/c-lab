#include "memory_table.h"

wordNode *create_new_word_node(word value, int address, char *debug_name)
{
    wordNode *node = allocate_memory_with_check(sizeof(wordNode));

    node->value = value;
    node->address = address;
    
    if (debug_name)
        node->debug_name = allocate_memory_with_check(strlen(debug_name) + 1);
    strcpy(node->debug_name, debug_name);

    node->next = NULL;

    return node;
}

int add_node_to_list_word(wordNode **head, word value, int address, char *debug_name)
{
    wordNode *new_node, *current;

    if (IS_DEBUG_FIRST_PASS)
        printf("Adding word node to list: %s\n", debug_name);

    new_node = create_new_word_node(value, address, debug_name);

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

int set_value_by_address(wordNode *head, int address, word newValue)
{
    wordNode *current = head;
    while (current != NULL)
    {
        if (current->address == address)
        {
            current->value = newValue;
            return SUCCESS;
        }
        current = current->next;
    }
    return FAILURE;
}

/* Used for debugging */
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

/* Used for debugging */
void print_list_word_binary(char *name, wordNode *head)
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
        printf("\n\t[(debug_name:%s, address: %d, value: ", current->debug_name, current->address);
        print_bits(current->value);
        printf(")]");
        current = current->next;
        i++;
    }
    printf("\n");
}

/* Used for debugging */
void print_list_word_octal(char *name, wordNode *head)
{
    wordNode *current = head;
    int i = 0;
    printf("%s", name);
    while (current != NULL)
    {
        if (i)
        {
            printf(" -> ");
        }
        printf("\n\t[(debug_name:%s, address: %d, value: %05o)]", current->debug_name, current->address, get_word_15bits(current->value));
        current = current->next;
        i++;
    }
    printf("\n");
}

void free_node_word(wordNode *node1)
{
    if (node1->debug_name)
        soft_free_mem(node1->debug_name);
    soft_free_mem(node1);
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
