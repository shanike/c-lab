#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labels_table.h"
#include "generic_memory_allocation_functions.h"
#include "error_handling.h"

/* TODO merge with list_data_structure.c */

labelNode *create_new_label_node(char *name, FeatureType feature_type, int value)
{
    labelNode *node = allocate_memory_with_check(sizeof(labelNode));

    /* Copy the name to the node's pre-allocated name array */
    strcpy(node->name, name);

    node->feature_type = feature_type;
    node->value = value;
    node->next = NULL;

    return node;
}

labelNode *find_node_in_label_list(labelNode *head, char *name)
{
    labelNode *current = head;

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

/*
Internal utility function to add a node to the linked list.
*/
void internal_add_node_to_list(labelNode **head, char *name, FeatureType feature_type, int value)
{
    labelNode *new_node, *current;

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
}

int add_node_to_labels_list(labelNode **head, char *name, FeatureType feature_type, int value, location_in_file location)
{
    labelNode *node_exists;

    if (IS_DEBUG_FIRST_PASS)
        printf("Adding node label: %s of %d\n", name, feature_type);
    node_exists = find_node_in_label_list(*head, name);
    if (IS_DEBUG_FIRST_PASS)
        printf("Node exists: %s\n", !node_exists ? "~Nope~" : node_exists->name);
    if (node_exists != NULL)
    {
        print_file_error(ERROR_STATUS_CODE_112, location);
        free(name);
        return FAILURE;
    }

    internal_add_node_to_list(head, name, feature_type, value);
    return SUCCESS;
}

/*
Different from add_node_to_labels_list in that it doesn't check if the node already exists.
*/
void add_node_to_externals_list(labelNode **head, char *name, int value)
{
    if (IS_DEBUG_SECOND_PASS)
        printf("Adding node external: %s\n", name);

    internal_add_node_to_list(head, name, -1, value);
}

int set_label_as_entry(labelNode **head, char *name)
{
    labelNode *label = find_node_in_label_list(*head, name);
    if (IS_DEBUG_SECOND_PASS)
        printf("Setting label as entry: %s\n", label ? label->name : "NULL");
    if (!label)
    {
        /* TODO what if label is not defined? */
        return FAILURE;
    }

    label->feature_type = ENTRY;
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

void create_labels_output_file(char *base_filename,
                               char *file_extension,
                               labelNode *list,
                               char *format,
                               filter_f filter)
{
    labelNode *current = list;
    char *output_filename = NULL;
    FILE *fp = NULL;

    int found_items = 0;

    if (current == NULL)
        /* No items to write. Break before mallocs */
        return;

    output_filename = create_new_file_name(base_filename, file_extension);
    if (output_filename == NULL)
    {
        return;
    }

    if (!open_file_for_writing(output_filename, &fp))
    {
        free(output_filename);
        return;
    }

    while (current != NULL)
    {
        if (filter == NULL || filter(current))
        {
            found_items = 1;
            fprintf(fp, format, current->name, current->value);
        }
        current = current->next;
    }

    if (!found_items)
    {
        remove(output_filename);
    }

    free(output_filename);
    fclose(fp);
}

/* Free memory allocated for the name, content and node */
void free_node_label(labelNode *node1)
{
    soft_free_mem(node1);
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
