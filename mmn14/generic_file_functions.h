
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "./global_variables.h"

/* Function prototypes */

/* Function to open the file for reading and handle errors */
int open_file_for_reading(const char *file_name, FILE **fp);

/* Function to open the file for writing and handle errors */
int open_file_for_writing(const char *file_name, FILE **fp_out);

/* Open file for writing only if file is not yet open */
int soft_open_file_for_writing(const char *file_name, FILE **fp_out);

/* Close file only if file is open */
void soft_fclose(FILE **fp);

/* Function to create a new file name with the specified extension */
char *create_new_file(const char *base_file_name, const char *extension);

/* Function to copy the contents of one file to another */
int copy_file(const char *destination_file_name, const char *source_file_name);

/**
 * @brief Cleans up the specified file by deleting it and freeing the memory allocated for the file path.
 *
 * This function removes the file located at the given file path.
 * The function also frees the memory allocated for the file path.
 *
 * @param file_path A pointer to the file path to be cleaned up. The memory allocated for
 *                  this file path will be freed by this function.
 */
void cleanup_file(char *file_path);

/**
 * Allocates memory and checks if the allocation was successful.
 *
 * @param size The size of the memory to allocate.
 * @return Pointer to the allocated memory if successful, or NULL if the allocation fails.
 */
void *allocate_memory_with_check(long size);

/* Function to remove extra spaces in a given line */
void remove_extra_spaces_in_line(char line[]);

/* Function to remove extra spaces from a file and save the result to a new file */
char *remove_extra_spaces_in_file(char file_name[]);

/* Function to copy text from a file starting at a given position up to a specified length */
char *copy_text(FILE *fp, fpos_t *start_pos, int text_length);

#endif /* UTILS_H */
