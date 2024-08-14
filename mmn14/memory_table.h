#ifndef MEMORY_TABLE_H
#define MEMORY_TABLE_H

#include "./global_variables.h"

typedef unsigned int word;

/* A node in a linked list */
struct wordNode
{
    word value;
    int address;
    char temp_name[4]; /* TODO temp */
    struct wordNode *next;
};
typedef struct wordNode wordNode;

/* Function prototypes */

/**
 * Creates a new node.
 *
 * @param value The value of the node.
 * @param address The address of the node.
 * @return A pointer to the new node.
 */
wordNode *create_new_word_node(word value, int address, char *temp_name);

/**
 * Adds a new node to the end of the linked list.
 *
 * @param head Pointer to the head of the list.
 * @param value The value of the new node.
 * @param address The address of the new node.
 * @return SUCCESS if the node was added successfully, FAILURE otherwise.
 */
int add_node_to_list_word(wordNode **head, word value, int address, char *temp_name);

/**
 * Prints the linked list in binary format.
 *
 * @param head Pointer to the head of the list to print.
 */
void print_list_word_binary(wordNode *head);

/**
 * Prints the linked list in octal format.
 *
 * @param head Pointer to the head of the list to print.
 */
void print_list_word_octal(wordNode *head);

/**
 * Frees the memory allocated for a node.
 *
 * @param node1 Pointer to the node to free.
 */
void free_node_word(wordNode *node1);

/**
 * Frees the memory allocated for all nodes in the linked list.
 *
 * @param head Pointer to the head of the list to free.
 */
void free_list_word(wordNode *head);

/**
 * Prints the bits of a number, left to right.
 *
 * @param num The number to print.
 */
void print_bits(word num);

#endif /* MEMORY_TABLE_H */