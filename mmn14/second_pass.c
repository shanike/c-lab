#include <stdio.h>
#include "second_pass.h"
#include "error_handling.h"
#include "generic_file_functions.h"
#include "global_variables.h"
#include "memory_table.h"

int create_ob_file(wordNode *instructions, int count, char *input_file_name, int IC, int DC)
{
    int i, address, word_content;
    FILE *ob_fp;
    char *ob_file_name;

    /* Create the output file name with an '.ob' extension */
    ob_file_name = create_new_file(input_file_name, OBJECT_FILE_EXT);

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

