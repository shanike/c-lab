#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>

#include "labels_table.h"
#include "memory_table.h"

#define SUCCESS 1
#define FAILURE 0

/**
 * Creates an object file (.ob) from the given instructions.
 *
 * Writes the IC and DC values to the first line of the object file, followed by
 * the instructions in the specified format.
 *
 * @param instructions A linked list of instructions.
 * @param count The number of instructions.
 * @param input_file_name The name of the input file.
 * @param IC The instruction counter.
 * @param DC The data counter.
 * @return SUCCESS if the object file was created successfully, FAILURE otherwise.
 */
int create_ob_file(wordNode *instructions, int count, char *input_file_name, int IC, int DC);

/**
 * Executes the second pass of the assembler.
 *
 * Opens the input file for reading and creates the object file (.ob) and entries file (.ent).
 *
 * @param input_file_name The name of the input file.
 * @param labels_table A linked list of labels.
 * @param IC The instruction counter.
 * @param DC The data counter.
 * @param instructions A linked list of instructions.
 * @param data A linked list of data.
 * @return SUCCESS if the second pass was executed successfully, FAILURE otherwise.
 */
int exec_second_pass(char *input_file_name, labelNode *labels_table, int IC, int DC, wordNode *instructions, wordNode *data);

#endif
