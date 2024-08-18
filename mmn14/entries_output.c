#include "entries_output.h"

void create_entries_file(labelNode *labels_table, char *filename)
{
    labelNode *current_label = labels_table;
    char *entries_filename = NULL;
    FILE *entries_fp = NULL;

    if (current_label == NULL)
    {
        return;
    }

    /* Set entries filename */
    entries_filename = create_new_file_name(filename, ENTRY_FILE_EXT);
    if (entries_filename == NULL)
    {
        return;
    }

    if (open_file_for_writing(entries_filename, &entries_fp) == FAILURE)
    {
        free(entries_filename);
        return;
    }

    /* Find entry labels and fill file */
    while (current_label)
    {
        if (current_label->feature_type == ENTRY)
        {
            fprintf(entries_fp, "%s %03d\n", current_label->name, current_label->value);
        }
        current_label = current_label->next;
    }

    fclose(entries_fp);
    free(entries_filename);
}
