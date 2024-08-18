#ifndef MACROS_TABLE_H
#define MACROS_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic_memory_allocation_functions.h"
#include "error_handling.h"

/* A node in a macro linked list */
typedef struct macroNode
{
    char *name;             /* Name associated with the macro */
    char *content;          /* Macro content stored in the node */
    int line_number;        /* Line number associated with the content */
    struct macroNode *next; /* Pointer to the next macro in the linked list */
} macroNode;

/* Function prototypes */

/**
 * Creates a new macro node and allocates memory for it.
 *
 * @param name The name to store in the macro node.
 * @param content The content to store in the macro node.
 * @param line_number The line number associated with the content.
 * @return Pointer to the newly created macro node.
 */
macroNode *create_new_macro_node(char *name, char *content, int line_number);

/**
 * Finds a given macro node name in the list and return it if it was found.
 *
 * @param head Pointer to the head pointer of the list.
 * @param name The name we want to find.
 * @return Pointer to the macro node if found and if not, return NULL.
 */
macroNode *find_node_in_macro_list(macroNode *head, char *name);

/**
 * Adds a new macro node to the linked list.
 *
 * @param head Pointer to the head pointer of the list.
 * @param name The name to store in the new macro node.
 * @param content The content to store in the new macro node.
 * @param line_number The line number associated with the content.
 * @return SUCCESS if the node was added successfully and FAILURE if not.
 */
int add_node_to_macro_list(macroNode **head, char *name, char *content, int line_number);

/**
 * Frees the memory allocated for a node.
 *
 * @param node Pointer to the node to free.
 */
void free_node(macroNode *node);

/**
 * Frees the memory allocated for all nodes in the macro list.
 *
 * @param head Pointer to the head of the macro list to free.
 */
void free_macro_list(macroNode *head);

#endif /* MACROS_TABLE_H */
