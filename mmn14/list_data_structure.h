#ifndef LIST_DATA_STRUCTURE_H
#define LIST_DATA_STRUCTURE_H

/* A node in a linked list */
typedef struct node {
    char *name;         /* Name associated with the node */
    char *content;      /* Content stored in the node */
    int line_number;           /* Line number associated with the content */
    struct node *next;  /* Pointer to the next node in the linked list */
} node;

/* Function prototypes */

/**
 * Creates a new node and allocates memory for it.
 *
 * @param name The name to store in the node.
 * @param content The content to store in the node.
 * @param line_number The line number associated with the content.
 * @return Pointer to the newly created node.
 */
node *create_new_node(char *name, char *content, int line_number);

/**
 * Finds a given node name in the list and return it if it was found.
 *
 * @param head Pointer to the head pointer of the list.
 * @param name The name we want to find.
 * @return Pointer to the node if found and if not, return NULL.
 */
node *find_node_in_list(node *head, char *name);

/**
 * Adds a new node to the linked list.
 *
 * @param head Pointer to the head pointer of the list.
 * @param name The name to store in the new node.
 * @param content The content to store in the new node.
 * @param line_number The line number associated with the content.
 */
void add_node_to_list(node **head, char *name, char *content, int line_number);

/**
 * Frees the memory allocated for a node.
 *
 * @param node1 Pointer to the node to free.
 */
void free_node(node *node1);

/**
 * Frees the memory allocated for all nodes in the linked list.
 *
 * @param head Pointer to the head of the list to free.
 */
void free_list(node *head);

#endif /* LIST_DATA_STRUCTURE_H */
