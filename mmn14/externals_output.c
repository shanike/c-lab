#include "externals_output.h"

void create_externals_file(labelNode *externals, char *input_filename)
{
    create_labels_output_file(input_filename, EXTERN_FILE_EXT, externals, "%s\t%04d\n", NULL);
}
