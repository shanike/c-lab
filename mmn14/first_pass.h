#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "labels_table.h"
#include "memory_table.h"
#include "first_pass.h"
#include "global_variables.h"
#include "generic_memory_allocation_functions.h"
#include "validations.h"
#include "text_functions.h"
#include "error_handling.h"
#include "encoding.h"

/*
Main function of first_pass.
The function reads the input file and encodes into the instructions and data tables everything but the labels.
In the process, the IC, DC values, and the labels_list, instructions_table and data_table pointers are updated.

The function returns SUCCESS if the first pass was successful, FAILURE otherwise.
*/
int first_pass(char filename[],
               labelNode **labels_list,
               wordNode **instructions_table,
               wordNode **data_table,
               int *IC,
               int *DC);

#endif
