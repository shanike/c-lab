#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./global_variables.h"
#include "./pre_assembler.h"
#include "./error_handling.h"
#include "./validations.h"
#include "./generic_file_functions.h"

#define SUCCESS 1
#define FAILURE 0

char *extract_macro_content(FILE *fp, fpos_t *position, int *line_count)
{
    int macro_content_length = 0;
    char str[MAX_LINE_LENGTH];

    /* Set the file pointer to the provided position */
    if (fsetpos(fp, position) != 0)
    {
        print_system_error(ERROR_STATUS_CODE_105);
        return NULL;
    }

    str[0] = '\0';

    /* Read lines from the file until "endmacr" is encountered which signifies the end of the macro*/
    while (fgets(str, MAX_LINE_LENGTH, fp) && (strcmp(str, "endmacr\n")) != 0)
    {
        /* Validation - Check for a line with "endmacr" and extra text with it, and if so, print error */
        if ((strstr(str, MACRO_END) != NULL) && strlen(str) != strlen(MACRO_END))
        {
            print_system_error(ERROR_STATUS_CODE_106);
            return NULL;
        }

        (*line_count)++;

        /* The length of each line is added to macro_length. */
        macro_content_length += strlen(str);
    }

    /* Copy the macro content into a dynamically allocated string */
    return copy_text(fp, position, macro_content_length);
}

int is_macro_declaration_valid(char *str, char **p_macro_name, int line_counter, char *file_name)
{
    char *temp_macro_name, *extra;

    /* Extract and check the macro name directly */
    temp_macro_name = strtok(NULL, " \n");
    if (temp_macro_name == NULL)
    {
        print_system_error(ERROR_STATUS_CODE_103);
        return FAILURE;
    }

    /* Check if the macro name clashes with instruction name, opcode, or register name */
    if (is_instruction(temp_macro_name) || is_opcode(temp_macro_name) || is_register(temp_macro_name))
    {
        location_in_file as_file;
        as_file.file_name = file_name;
        as_file.line_number = line_counter;
        print_file_error(ERROR_STATUS_CODE_109, as_file);
        return FAILURE;
    }

    /* Check for extra text after the macro name */
    extra = strtok(NULL, "\n");
    if (extra != NULL)
    {
        print_system_error(ERROR_STATUS_CODE_104);
        return FAILURE;
    }

    /* Copy the extracted macro name into a dynamically allocated string */
    *p_macro_name = allocate_memory_with_check((strlen(temp_macro_name) + 1) * sizeof(char));
    strcpy(*p_macro_name, temp_macro_name);

    return SUCCESS;
}

/* Scan and save all the macros in the given file in a linked list of macros */
int collect_macros_to_linked_list(char *file_name, node **macro_list_head)
{
    int line_counter = 0;
    int is_successful = SUCCESS;
    FILE *fp;                  /* A file pointer to read the given file*/
    char str[MAX_LINE_LENGTH]; /* A buffer to store lines read from the given file */

    /* Open the file for reading */
    if (open_file_for_reading(file_name, &fp) == FAILURE)
        return FAILURE;

    /* Read each line of the given file */
    while (fgets(str, MAX_LINE_LENGTH, fp))
    {
        line_counter++;

        /* Extract the macro name from the declaration line and validate it */
        /* Check if the line starts with "mcro" which is a macro declaration */
        if (strcmp(strtok(str, " "), MACRO_DECLARATION) == 0)
        {

            if (process_macro_declaration(fp, &line_counter, macro_list_head, file_name) == FAILURE)
            {
                is_successful = FAILURE;
                /* TODO: should we add a `break` here? */
            }
        }
    }

    /*Close the file and return the value of is_successful */
    fclose(fp);
    return is_successful;
}

/* Function to process a macro declaration */
int process_macro_declaration(FILE *fp, int *line_counter, node **macro_list_head, char *file_name)
{
    char *name, *content;
    fpos_t file_position;
    int macro_line = *line_counter;

    /* Validate the macro declaration */
    if (!is_macro_declaration_valid(NULL, &name, *line_counter, file_name))
    {
        return FAILURE;
    }

    /* Save the current file position */
    fgetpos(fp, &file_position);

    /* Save the macro content starting from the current file position */
    content = extract_macro_content(fp, &file_position, line_counter);
    if (content == NULL)
    {
        return FAILURE;
    }

    /* Reset the file pointer to the end of the macro */
    fsetpos(fp, &file_position);

    /* Add the new macro to the macro list */
    add_node_to_list(macro_list_head, name, content, macro_line);
    return SUCCESS;
}

/* Remove the declaration of the macros from the input file and save the result in the same temp file */
int filter_macro_declarations(char file_name[])
{
    char *line_token, *filtered_file_name;
    char line[MAX_LINE_LENGTH];
    char line_copy[MAX_LINE_LENGTH];
    FILE *input_file, *output_file;

    /* Open the file for reading */
    if (open_file_for_reading(file_name, &input_file) == FAILURE)
        return FAILURE;

    /* Create a new filename with the ".temp2" extension */
    filtered_file_name = create_new_file(file_name, ".temp2");

    /* Open the new file for writing */
    if (!open_file_for_writing(filtered_file_name, &output_file))
    {
        cleanup_resources(4, "file", input_file, "%s", output_file);
        return FAILURE;
    }

    /* Process the input file line by line and don't write related lines to macros */
    while (fgets(line, MAX_LINE_LENGTH, input_file))
    {
        /* Copy the line to the variable line_copy*/
        strcpy(line_copy, line);
        line_token = strtok(line, " \n");

        /* We are now at a blank line, so continue to the next line */
        if (line_token == NULL)
        {
            fprintf(output_file, "\n");
            continue;
        }

        /* A macro was found, now skip the lines belongs to the macro */
        if (strcmp(line_token, MACRO_DECLARATION) == 0)
        {
            /* Skip lines until we find "endmacr" which indicates we are at the end of the macro */
            while (strcmp(line_token, MACRO_END) != 0)
            {
                if (!fgets(line, MAX_LINE_LENGTH, input_file))
                    break;
                line_token = strtok(line, " \n");

                /* Skip blank lines within the macro */
                while (line_token == NULL)
                {
                    fprintf(output_file, "\n");
                    if (!fgets(line, MAX_LINE_LENGTH, input_file))
                        break;
                    line_token = strtok(line, " \n");
                }
            }
        }
        else
        {
            /* Write the line to the new file since it's not part of a macro */
            fprintf(output_file, "%s", line_copy);
        }
    }
    /* Close file pointers */
    fclose(input_file);
    fclose(output_file);

    copy_file(file_name, filtered_file_name);

    return SUCCESS;
}

void extract_line_parts(const char *line, const char *macro_name, char *start_part, char *end_part)
{
    const char *macro_position = strstr(line, macro_name);

    /* Copy the part of the line before the macro name */
    strncpy(start_part, line, macro_position - line);
    start_part[macro_position - line] = '\0';

    /* Copy the part of the line after the macro name */
    strcpy(end_part, macro_position + strlen(macro_name));
}

char *replace_macro_in_line(char *line, node *macro)
{
    char start_part[MAX_LINE_LENGTH];
    char end_part[MAX_LINE_LENGTH];
    char *new_line;

    /* Extract parts of the line before and after the macro */
    extract_line_parts(line, macro->name, start_part, end_part);

    /* Allocate memory for the new line with the macro content replaced */
    new_line = allocate_memory_with_check((strlen(start_part) + strlen(macro->content) + strlen(end_part) + 1) * sizeof(char));
    if (new_line == NULL)
    {
        return new_line;
    }

    /* Construct the new line by concatenating the parts */
    strcpy(new_line, start_part);
    strcat(new_line, macro->content);
    strcat(new_line, end_part);

    /* Return the modified line */
    return new_line;
}

/* Process each line of the input file and write the macro's content instead of the declaration in the output file (the final file) */
int process_macros_in_file(FILE *input_file, FILE *output_file, node *macro)
{
    char line[MAX_LINE_LENGTH];
    char *modified_line;
    char *macro_position;

    while (fgets(line, MAX_LINE_LENGTH, input_file))
    {
        macro_position = strstr(line, macro->name);
        if (macro_position != NULL)
        {
            /* Remove the newline character at the end of the line */
            line[strlen(line) - 1] = '\0';
            modified_line = replace_macro_in_line(line, macro);
            /* Failure in replacing the macro */
            if (modified_line == NULL)
            {
                return FAILURE;
            }
            fprintf(output_file, "%s", modified_line);
            free(modified_line);
        }
        else
        {
            fprintf(output_file, "%s", line);
        }
    }

    /*  Successfully processed the macros in the file */
    return SUCCESS;
}

char *replace_all_macros_in_file(char file_name[], node *head)
{
    node *current_macro = head;
    char *temp_file_name, *final_file_name;
    FILE *input_temp_file, *output_file;

    /* Create a temporary files */
    temp_file_name = create_new_file(file_name, ".tmp");
    final_file_name = create_new_file(file_name, ".am");

    /* Copy the original file to both temporary and final files */
    if (!copy_file(temp_file_name, file_name) ||
        !copy_file(final_file_name, file_name))
    {
        /* Copying file failed - closing open files and freeing allocated memory */
        print_system_error(ERROR_STATUS_CODE_107);
        cleanup_resources(4, "%s", temp_file_name, "%s", final_file_name);
        return NULL;
    }

    current_macro = head;
    /* Process each macro in the macro list */
    while (current_macro != NULL)
    {
        if (open_file_for_reading(temp_file_name, &input_temp_file) == FAILURE)
        {
            cleanup_resources(4, "%s", temp_file_name, "%s", final_file_name);
            return FAILURE;
        }

        /* Open the final modified file for writing */
        if (!open_file_for_writing(final_file_name, &output_file))
        {
            cleanup_resources(6, "file", input_temp_file, "%s", temp_file_name, "%s", output_file);
            return FAILURE;
        }

        /* Process each line of the temporary file and change each macro declaration to the macro's content*/
        if (!process_macros_in_file(input_temp_file, output_file, current_macro))
        {
            cleanup_resources(8, "file", output_file, "file", input_temp_file, "%s", temp_file_name, "%s", final_file_name);
            return NULL;
        }

        /* Close the temporary and final modified files */
        fclose(input_temp_file);
        fclose(output_file);

        current_macro = current_macro->next;
        if (current_macro != NULL)
        {
            remove(temp_file_name);
            rename(final_file_name, temp_file_name);
        }
    }

    remove(temp_file_name);
    free(temp_file_name);

    /* Return the name of the final modified file */
    return final_file_name;
}

int process_macros(char file_name[])
{
    node *macro_list_head = NULL; /* A linked list of macros */
    char *temp_file, *final_file, *temp_file_name;

    /* TODO: check whether lines of comment (== ";") or empty/whitespace lines should be included in .am file (=the pre-assembler output)*/
    /* Remove unnecessary white spaces in the file and save the result in a new temp file */
    temp_file = remove_extra_spaces_in_file(file_name);

    /* If file is empty -> return 0 */
    if (temp_file == NULL)
        return FAILURE;

    /* Scan and save all the macros in the temp_file in a linked list of macros */
    if (!collect_macros_to_linked_list(temp_file, &macro_list_head))
    {
        /* If something went wrong or one of the macros is not valid -> return -*/
        free_list(macro_list_head);
        cleanup_resources(2, "%s", temp_file);
        return FAILURE;
    }
    
    if (!filter_macro_declarations(temp_file))
    {
        free_list(macro_list_head);
        cleanup_resources(2, "%s", temp_file);
        print_system_error(ERROR_STATUS_CODE_108);
        return FAILURE;
    }

    /* Replace all macro calls with their definitions as saved in the linked list and save the result in the final file */
    final_file = replace_all_macros_in_file(temp_file, macro_list_head);
    if (final_file == NULL)
    {
        free_list(macro_list_head);
        cleanup_resources(4, "%s", temp_file);
        print_system_error(ERROR_STATUS_CODE_108);
        return FAILURE;
    }

    temp_file_name = create_new_file(file_name, ".temp1");
    remove(temp_file_name);
    free(temp_file_name);

    /* Free allocated memory */
    free(temp_file);
    free(final_file);
    free_list(macro_list_head);

    /* Successfully processed the macros in the given file*/
    return SUCCESS;
}
