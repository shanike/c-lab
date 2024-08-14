#ifndef LABELS_TABLE_H
#define LABELS_TABLE_H

#include "./global_variables.h"

enum FEATURE_TYPE
{
    DATA,
    EXTERNAL,
    CODE
};
typedef enum FEATURE_TYPE FeatureType;

/* A node in a linked list */
struct labelNode
{
    char name[MAX_LABEL_LENGTH]; /* Name associated with the node */
    FeatureType feature_type;    /* Feature type of the label */
    int value;                   /* Memory address of the label */
    struct labelNode *next;      /* Pointer to the next node in the linked list */
};
typedef struct labelNode labelNode;

/* Function prototypes */

/**
 * Creates a new node and allocates memory for it.
 *
 * @param name The name to store in the node.
 * @return Pointer to the newly created node.
 */
labelNode *create_new_label_node(char *name, FeatureType feature_type, int value);

/**
 * Adds a new node to the linked list.
 * 
 * If the node already exists in the list, the function will print an error message and return FAILURE.
 *
 * @param head Pointer to the head pointer of the list.
 * @param name The name to store in the new node.
 */
int add_node_to_list_label(labelNode **head, char *name, FeatureType feature_type, int value, location_in_file location);

/**
 * Prints the linked list.
 */
void print_list_label(labelNode *head);

/**
 * Frees the memory allocated for a node.
 *
 * @param node1 Pointer to the node to free.
 */
void free_node_label(labelNode *node1);

/**
 * Frees the memory allocated for all nodes in the linked list.
 *
 * @param head Pointer to the head of the list to free.
 */
void free_list_label(labelNode *head);

#endif /* LABELS_TABLE_H */