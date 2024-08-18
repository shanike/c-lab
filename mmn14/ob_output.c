#include "ob_output.h"

int create_ob_file(wordNode *instructions, wordNode *data, char *input_file_name, int IC, int DC)
{
    int address, word_content;
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
    fprintf(ob_fp, "%d %d\n", IC, DC);

    /* Write each memory word (address and value) in the required format */

    while (instructions != NULL || data != NULL)
    {
        if (instructions != NULL)
        {
            address = instructions->address;
            word_content = instructions->value;
            instructions = instructions->next;
        }
        else
        {
            address = data->address;
            word_content = data->value;
            data = data->next;
        }

        /* Print address in 4-digit decimal format and content in 5-digit octal format */
        fprintf(ob_fp, "%04d %05o\n", address, get_word_15bits(word_content));
    }

    free(ob_file_name);
    fclose(ob_fp);

    return SUCCESS;
}
