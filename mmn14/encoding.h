#include "./memory_table.h"
#include "./validations.h"
#include "./labels_table.h"

/* Function to encode an operation */
int encode_instruction(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **memory_table, labelNode *labels_list);