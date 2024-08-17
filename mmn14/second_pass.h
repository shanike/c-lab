#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include <stdio.h>

#include "labels_table.h"
#include "memory_table.h"
#include "validations.h"
#include "generic_memory_allocation_functions.h"

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
int exec_second_pass(char *input_file_name, labelNode **labels_table, wordNode **instructions, wordNode **data, int IC, int DC);

#endif
