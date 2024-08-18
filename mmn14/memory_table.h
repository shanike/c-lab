#ifndef MEMORY_TABLE_H
#define MEMORY_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global_variables.h"
#include "generic_file_functions.h"
#include "generic_memory_allocation_functions.h"
#include "error_handling.h"
#include "bitwise_functions.h"


/* A node in a linked list */
struct wordNode
{
    word value;
    int address;
    char *debug_name; /* Used for debugging */
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
wordNode *create_new_word_node(word value, int address, char *debug_name);

/**
 * Adds a new node to the end of the linked list.
 *
 * @param head Pointer to the head of the list.
 * @param value The value of the new node.
 * @param address The address of the new node.
 * @return SUCCESS if the node was added successfully, FAILURE otherwise.
 */
int add_node_to_list_word(wordNode **head, word value, int address, char *debug_name);

/**
 * Sets the value of a node by its address.
 *
 * @param head Pointer to the head of the list.
 * @param address The address of the node to update.
 * @param newValue The new value of the node.
 * @return SUCCESS if the value was found and updated successfully, FAILURE otherwise.
 */
int set_value_by_address(wordNode *head, int address, word newValue);

/**
 * Prints the linked list in binary format.
 *
 * @param head Pointer to the head of the list to print.
 */
void print_list_word_binary(char *name, wordNode *head);

/**
 * Prints the linked list in octal format.
 *
 * @param head Pointer to the head of the list to print.
 */
void print_list_word_octal(char *name, wordNode *head);

/**
 * Returns the lower 15 bits of a word.
 */
int get_word_15bits(word word);

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
