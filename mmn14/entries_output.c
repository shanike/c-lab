#include <stdio.h>
#include "entries_output.h"

int create_entries_output(labelNode *labels_table, char *filename)
{
    labelNode *current_label = labels_table;
    char *entries_filename = NULL;
    FILE *entries_fp = NULL;

    /* Set entries filename */
    entries_filename = create_new_file(filename, ENTRY_FILE_EXT);
    if (entries_filename == NULL)
    {
        return FAILURE;
    }

    /* Find entries and fill file */
    while (current_label)
    {
        if (current_label->feature_type == ENTRY)
        {
            soft_open_file_for_writing(entries_filename, &entries_fp);
            fprintf(entries_fp, "%s %03d\n", current_label->name, current_label->value);
        }
        current_label = current_label->next;
    }

    soft_fclose(&entries_fp);

    free(entries_filename);

    return SUCCESS;
}
