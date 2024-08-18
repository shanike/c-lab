#ifndef EXTERNAL_OUTPUT_H
#define EXTERNAL_OUTPUT_H

#include <stdio.h>

#include "labels_table.h"
#include "global_variables.h"

/*
Writes the external-labels-usage into the correct output file, according to the provided externals list
*/
void create_externals_file(labelNode *externals, char *input_filename);

#endif
