#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./labels_table.h"
#include "./generic_file_functions.h"
#include "./error_handling.h"
#include "./global_variables.h"

/* TODO merge with list_data_structure.c */

labelNode *create_new_label_node(char *name, FeatureType feature_type, int value)
{
    labelNode *node;

    /* Check if memory allocation for the node succeeded */
    node = allocate_memory_with_check(sizeof(labelNode));

    /* Copy the name to the node's name array */
    strcpy(node->name, name);

    node->feature_type = feature_type;
    node->value = value;

    node->next = NULL;

    return node;
}

labelNode *find_node_in_list_label(labelNode *head, char *name)
{
    labelNode *current = head;

    while (current != NULL)
    {
        /* If the node exists already */
        if (strcmp(name, current->name) == 0)
        {
            return head;
        }
        current = current->next;
    }

    return NULL;
}

int add_node_to_list_label(labelNode **head, char *name, FeatureType feature_type, int value, location_in_file location)
{
    labelNode *new_node, *current, *node_exists;

    if (IS_DEBUG)
        printf("Adding node: %s of %d\n", name, feature_type);
    node_exists = find_node_in_list_label(*head, name);
    if (IS_DEBUG)
        printf("Node exists: %s\n", !node_exists ? "~Nope~" : node_exists->name);
    if (node_exists != NULL)
    {
        print_file_error(ERROR_STATUS_CODE_112, location);
        free(name);
        return FAILURE;
    }

    new_node = create_new_label_node(name, feature_type, value);

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

void print_list_label(labelNode *head)
{
    labelNode *current = head;
    int i = 0;
    printf("List: ");
    while (current != NULL)
    {
        if (i)
        {
            printf(" -> ");
        }
        printf("\n\t[%s (value: %d, feature: %d)]", current->name, current->value, current->feature_type);
        current = current->next;
        i++;
    }
    printf("\n");
}

void free_node_label(labelNode *node1)
{
    /* Free memory allocated for the name, content and node */
    free(node1->name);
    free(node1);
}

void free_list_label(labelNode *head)
{
    /* Go through the linked list and free memory allocated fot each node in the list */
    while (head != NULL)
    {
        labelNode *temp = head;
        head = head->next;
        free_node_label(temp);
    }
}