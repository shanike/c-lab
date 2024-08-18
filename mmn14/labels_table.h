#ifndef LABELS_TABLE_H
#define LABELS_TABLE_H

#include "global_variables.h"

enum FEATURE_TYPE
{
    DATA,
    EXTERNAL,
    CODE,
    ENTRY /* Used on second-pass to override DATA or CODE labels to ENTRY, if declared as so */
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

/* Function pointer type for filtering labels */
typedef int (*filter_f)(labelNode *);

/* Function prototypes */

/**
 * Creates a new node and allocates memory for it.
 *
 * @param name The name to store in the node.
 * @return Pointer to the newly created node.
 */
labelNode *create_new_label_node(char *name, FeatureType feature_type, int value);

/**
 * Finds a node in the linked list.
 *
 * @param head Pointer to the head of the list.
 * @param name The name to search for.
 * @return Pointer to the node if found, NULL otherwise.
 */
labelNode *find_node_in_list_label(labelNode *head, char *name);

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
 * Adds a new node to the linked list, without checking if the node already exists.
 */
void add_node_to_list_externals(labelNode **head, char *name, int value);

/**
 * Sets the feature type of an existing label in the linked list to ENTRY.
 *
 * @param head Pointer to the head of the list.
 * @param name The name of the label to set as ENTRY.
 * @return SUCCESS if the label was found and set as ENTRY, FAILURE otherwise.
 */
int set_label_as_entry(labelNode **head, char *name);

/**
 * Creates a new file with the labels and their memory addresses.
 *
 * @param base_filename The base filename to use for the new file.
 * @param file_extension The file extension to use for the new file.
 * @param list Pointer to the head of the linked list.
 * @param format The format string to use for the output.
 * @param filter A pointer to a function which filters the labels to include in the output. (NULL for no filter).
 */
void create_labels_output_file(char *base_filename, char *file_extension, labelNode *list, char *format, filter_f filter);

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
