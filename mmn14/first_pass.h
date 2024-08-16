#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "labels_table.h"
#include "memory_table.h"

/* Main function of first_pass */
int first_pass(char filename[],
               labelNode **labels_list,
               wordNode **instructions_table,
               wordNode **data_table,
               int *IC,
               int *DC);

#endif
