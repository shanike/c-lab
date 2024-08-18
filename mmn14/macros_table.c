#include "macros_table.h"

macroNode *create_new_macro_node(char *name, char *content, int line_number)
{
    macroNode *temp = allocate_memory_with_check(sizeof(macroNode));

    temp->name = name;
    temp->content = content;
    temp->line_number = line_number;
    temp->next = NULL;

    return temp;
}

macroNode *find_node_in_macro_list(macroNode *head, char *name)
{
    macroNode *current = head;

    while (current != NULL)
    {
        /* If the node exists already */
        if (strcmp(name, current->name) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int add_node_to_macro_list(macroNode **head, char *name, char *content, int line_number)
{
    macroNode *new_node, *current, *macro_with_same_name;

    macro_with_same_name = find_node_in_macro_list(*head, name);

    /* If we found another macro declaration with the same name but not with the same content, throw error */
    if (macro_with_same_name != NULL && strcmp(macro_with_same_name->content, content) != 0)
    {
        print_system_error(ERROR_STATUS_CODE_111);
        free(name);
        free(content);
        return FAILURE;
    }

    new_node = create_new_macro_node(name, content, line_number);

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

void free_node(macroNode *node)
{
    /* Free memory allocated for the name, content and node */
    free(node->name);
    free(node->content);
    free(node);
}

void free_macro_list(macroNode *head)
{
    /* Go through the linked list and free memory allocated fot each node in the list */
    while (head != NULL)
    {
        macroNode *temp = head;
        head = head->next;
        free_node(temp);
    }
}
