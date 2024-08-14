#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "./generic_file_functions.h"
#include "./text_functions.h"
#include "./error_handling.h"
#include "./global_variables.h"

/*
Function to open the file for reading and handle errors.
Returns success/failure code
*/
int open_file_for_reading(const char *file_name, FILE **fp)
{
    *fp = fopen(file_name, "r");
    if (*fp == NULL)
    {
        print_system_error(ERROR_STATUS_CODE_102);
        return FAILURE;
    }
    return SUCCESS;
}

/* Function to open the file for writing and handle errors */
int open_file_for_writing(const char *file_name, FILE **fp_out)
{
    *fp_out = fopen(file_name, "w");
    if (*fp_out == NULL)
    {
        print_system_error(ERROR_STATUS_CODE_101);
        return FAILURE;
    }
    return SUCCESS;
}

/* TODO: rename to create_new_filename ?*/
char *create_new_file(const char *base_file_name, const char *extension)
{
    char *new_file_name, *extension_position;

    /* TODO: maybe change length of allocation to length of `base_file_name` + length of `extension`?. */
    /* Allocate memory for the new file name */
    new_file_name = allocate_memory_with_check(MAX_LINE_LENGTH * sizeof(char));
    if (new_file_name == NULL)
    {
        return NULL;
    }

    /* Copy the base file name into the new file name */
    strcpy(new_file_name, base_file_name);

    /* Find the position of the last '.' in the file name */
    extension_position = strrchr(new_file_name, '.');
    if (extension_position != NULL)
    {
        /* If a '.' is found, truncate the file name at this position */
        new_file_name[extension_position - new_file_name] = '\0';
    }

    /* Concatenate the extension to the truncated file name */
    strcat(new_file_name, extension);

    return new_file_name;
}

/* Function to copy the contents of one file to another */
int copy_file(const char *destination_file_name, const char *source_file_name)
{
    char line_buffer[MAX_LINE_LENGTH];
    FILE *source_file, *destination_file;

    /* Open the source file for reading */
    if (!open_file_for_reading(source_file_name, &source_file))
        return FAILURE;

    /* Open the destination file for writing */
    if (!open_file_for_writing(destination_file_name, &destination_file))
    {
        fclose(source_file);
        return FAILURE;
    }

    /* Copy each line from the source file to the destination file */
    while (fgets(line_buffer, MAX_LINE_LENGTH, source_file) != NULL)
    {
        fputs(line_buffer, destination_file);
    }

    /* Close the files */
    fclose(source_file);
    fclose(destination_file);

    return SUCCESS;
}

/* Remove a given file */
void cleanup_file(char *file_path)
{
    /* Check if file path is not NULL */
    if (file_path != NULL)
    {
        /* Remove the file */
        remove(file_path);
        
        /* Free the allocated memory for the file path */
        free(file_path);
    }
    else
    {
        fprintf(stderr, "Invalid file path.\n");
    }
}

/* TODO exit() program */
/* Allocates memory and checks if the allocation was successful */
void *allocate_memory_with_check(long size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        /* Report the memory allocation failure */
        print_system_error(ERROR_STATUS_CODE_100);
    }
    return ptr;
}

/* todo - go through this function */
void remove_extra_spaces_in_line(char line[])
{
    /* i for original string, j for modified string */
    int i, j;
    char temp_line[MAX_LINE_LENGTH];
    i = j = 0;
    /* eliminating white-spaces in the beginning of the line */
    while (is_white_space_or_tab(*(line + i)))
    {
        i++;
    }
    while (*(line + i) != '\0')
    {
        /* copying character */
        while (!is_white_space_or_tab(*(line + i)) && *(line + i) != '\0')
        {
            *(temp_line + j) = *(line + i);
            i++;
            j++;
        }
        /* if loop stopped because end of line char */
        if (*(line + i) == '\0')
        {
            break;
        }
        /* if loop stopped because of a white-space skipping them until another character is encountered*/
        while (is_white_space_or_tab(*(line + i)))
        {
            i++;
        }
        /* if stopped not because of end of line char then copy one space for all the others that were skipped */
        if (!(*(line + i) == '\n' || *(line + i) == '\0'))
        {
            *(temp_line + j) = ' ';
            j++;
        }
    }
    *(temp_line + j) = *(line + i);
    *(temp_line + j + 1) = '\0';
    remove_spaces_next_to_comma(temp_line);
    strcpy(line, temp_line);
}

char *remove_extra_spaces_in_file(char file_name[])
{
    char *new_file_name;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    FILE *fp, *fp_temp;

    if (!open_file_for_reading(file_name, &fp))
        return NULL;

    new_file_name = create_new_file(file_name, ".temp1");
    if (new_file_name == NULL)
    {
        fclose(fp);
        return NULL;
    }

    if (!open_file_for_writing(new_file_name, &fp_temp))
    {
        fclose(fp);
        remove(new_file_name);
        free(new_file_name);
        return NULL;
    }

    /* Read each line of the input file and remove extra spaces */
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line_number++;
        if (strlen(line) > MAX_LINE_LENGTH)
        {
            location_in_file as_file;
            as_file.file_name = file_name;
            as_file.line_number = line_number;
            print_file_error(ERROR_STATUS_CODE_110, as_file);
            fclose(fp);
            fclose(fp_temp);
            return NULL;
        }
        /* Replace a comment line with newline character */
        else if (*line == ';')
        {
            *line = '\n';
            *(line + 1) = '\0';
        }
        else
            remove_extra_spaces_in_line(line);

        /* Save the changed line in the new file */
        fprintf(fp_temp, "%s", line);
    }

    fclose(fp);
    fclose(fp_temp);

    return new_file_name;
}

char *copy_text(FILE *fp, fpos_t *start_pos, int text_length)
{
    int index;
    char *text_buffer;

    /* Reset file pointer to the given position */
    if (fsetpos(fp, start_pos) != 0)
    {
        printf("fsetpos in copy_text failed\n");
        return NULL;
    }

    /* Allocate memory for the string to be copied, including space for the null terminator */
    text_buffer = allocate_memory_with_check((text_length + 1) * sizeof(char));

    /* Read characters from the file and copy them into the buffer */
    for (index = 0; index < text_length; index++)
    {
        *(text_buffer + index) = getc(fp);
    }
    text_buffer[text_length] = '\0';

    /* Save the current file position */
    fgetpos(fp, start_pos);
    return text_buffer;
}
