#include "./memory_table.h"
#include "./validations.h"

/* Function to encode an operation */
int encode_op(operation *op, char *args_str, location_in_file file_location, int *IC, wordNode **memory_table);
