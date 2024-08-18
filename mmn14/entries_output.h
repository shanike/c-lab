#ifndef ENTRIES_OUTPUT_H
#define ENTRIES_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "labels_table.h"
#include "global_variables.h"

/* Writes the entries into the correct output file, according to the provided labels table */
void create_entries_file(labelNode *labels_table, char *filename);

#endif
