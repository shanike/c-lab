#include "externals_output.h"

void create_externals_file(labelNode *externals, char *input_filename)
{
    FILE *fp;
    labelNode *current = externals;

    char *ext_filename = create_new_file_name(input_filename, EXTERN_FILE_EXT);

    if (current == NULL)
    {
        return;
    }
    
    if (!open_file_for_writing(ext_filename, &fp))
    {
        return;
    }
    while (current != NULL)
    {
        fprintf(fp, "%s\t%04d\n", current->name, current->value);
        current = current->next;
    }

    fclose(fp);
}