#include <stdio.h>
#include "second_pass.h"
#include "error_handling.h"
#include "generic_file_functions.h"
#include "global_variables.h"
#include "memory_table.h"
#include "entries_output.h"

int create_ob_file(wordNode *instructions, int count, char *input_file_name, int IC, int DC)
{
    int i, address, word_content;
    FILE *ob_fp;
    char *ob_file_name;

    /* Create the output file name with an '.ob' extension */
    ob_file_name = create_new_file_name(input_file_name, OBJECT_FILE_EXT);

    /* Open the new .ob file for writing */
    if (!open_file_for_writing(ob_file_name, &ob_fp))
    {
        fclose(ob_fp);
        return FAILURE;
    }

    /* Write the values of IC and DC in the first line of the ob file file */
    fprintf(ob_fp, "%d %d\n", IC + 100, DC);

    /* Write each memory word (address and value) in the required format */
    for (i = 0; i < count; i++)
    {
        address = 100 + i; /* Addressing starts at 100 */
        word_content = (instructions + i)->value;

        /* Print address in 4-digit decimal format and content in 5-digit octal format */
        fprintf(ob_fp, "%04d %05o\n", address, word_content);
    }

    free(ob_file_name);
    fclose(ob_fp);

    return SUCCESS;
}

/* TODO  what should we do with the data Node?? */
int exec_second_pass(char *input_file_name, labelNode *labels_table, int IC, int DC, wordNode *instructions, wordNode *data)
{
    FILE *fp, *ext_fp;
    int is_error = 0;
    location_in_file curr_location;
    char line[MAX_LINE_LENGTH], *ext_file_name;

    if (!open_file_for_reading(input_file_name, &fp))
    {
        is_error = 1;
    }

    curr_location.line_number = 0;
    curr_location.file_name = input_file_name;

    /* Create the output file name with an '.ext' extension */
    ext_file_name = create_new_file_name(input_file_name, EXTERN_FILE_EXT);

    /* Open the new '.ext' file for writing */
    if (!open_file_for_writing(ext_file_name, &ext_fp))
    {
        fclose(ext_fp);
        is_error = 1;
    }

    /* Read each line of the given file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {

        /* TODO Check if this line uses a label */

        /* TODO If so, replace each label usage in the table with the corresponding address in labels table */

        /* TODO For each extern type label , write it in the .ext file */
    }

    if (is_error == 1)
    {
        return FAILURE;
    }

    /* Create the outputs files ".ob" and ".ent" and write their data */
    create_ob_file(instructions, IC + DC, input_file_name, IC, DC);
    
    create_entries_output(labels_table, input_file_name);

    /* TODO Free all the allocated memory and resources used during the second pass */

    return SUCCESS;
}
