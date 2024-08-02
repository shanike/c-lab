#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./list_data_structure.h"
#include "./generic_file_functions.h"
#include "./error_handling.h"

node *create_new_node(char *name, char *content, int line_number)
{
    node *temp;

    /* Check if memory allocation for the node succeeded */
    temp = allocate_memory_with_check(sizeof(node));

    temp->name = name;
    temp->content = content;
    temp->line_number = line_number;
    temp->next = NULL;

    return temp;
}

node *find_node_in_list(node *head, char *name)
{
    node *current = head;

    while (current != NULL)
    {
        /* If the node exists already */
        if (strcmp(name, current->name) == 0)
        {
            printf("Node %s already exists in the list\n", name);
            return head;
        }
        current = current->next;
    }

    return NULL;
}

void add_node_to_list(node **head, char *name, char *content, int line_number)
{
    node *new_node, *current, *macro_with_same_name;

    macro_with_same_name = find_node_in_list(*head, name);

    /* If we found another macro declaration with the same name but not with the same content, throw error */
    if (macro_with_same_name != NULL && strcmp(macro_with_same_name->content, content) != 0)
    {
        print_system_error(ERROR_STATUS_CODE_111);
        free(name);
        free(content);
        return;
    }

    new_node = create_new_node(name, content, line_number);

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
}

void free_node(node *node1)
{
    /* Free memory allocated for the name, content and node */
    free(node1->name);
    free(node1->content);
    free(node1);
}

void free_list(node *head)
{
    /* Go through the linked list and free memory allocated fot each node in the list */
    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        free_node(temp);
    }
}
