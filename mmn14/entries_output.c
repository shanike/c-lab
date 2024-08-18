#include "entries_output.h"

int is_entry(labelNode *label)
{
    return label->feature_type == ENTRY;
}

void create_entries_file(labelNode *labels_table, char *filename)
{
    create_labels_output_file(filename, ENTRY_FILE_EXT, labels_table, "%s\t%d\n", is_entry);
}
