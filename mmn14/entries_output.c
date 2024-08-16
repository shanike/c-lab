#include <stdio.h>
#include "entries_output.h"

int create_entries_output(labelNode *labels_table, char *filename)
{
    labelNode *current_label = labels_table;
    char *entries_filename = create_new_file_name(filename, ENTRY_FILE_EXT);
    FILE *entries_fp;

    if (entries_filename == NULL)
    {
        return FAILURE;
    }

    if (!open_file_for_writing(entries_filename, &entries_fp))
    {
        return FAILURE;
    }
    printf("here\n");
    while (current_label)
    {
        if (current_label->feature_type == ENTRY)
        {
            fprintf(entries_fp, "%s %03d\n", current_label->name, current_label->value);
        }
        current_label = current_label->next;
    }

    fclose(entries_fp);

    return SUCCESS;
}
