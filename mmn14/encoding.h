#ifndef ENCODING_H
#define ENCODING_H

#include "memory_table.h"
#include "operation_utils.h"
#include "labels_table.h"
#include "generic_memory_allocation_functions.h"
#include "global_variables.h"
#include "error_handling.h"
#include "addressing_methods.h"
#include "bitwise_functions.h"
#include "a_r_e_fields.h"

/* Function to encode an operation */
int encode_instruction(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **instructions_table, labelNode *labels_list);

/*
Encodes the labels of an instruction line and adds external labels to the external file.
And fully updates the IC.
Important to notice that if the instruction line got to this function, most validations on it have already been done.
*/
int encode_labels(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **instructions_table, labelNode *labels_list, labelNode **externals_table);

#endif
