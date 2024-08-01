#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include <stdio.h>
#include "list_data_structure.h"

/* Function Prototypes */

/**
 * Extracts the content of a macro from a file.
 *
 * @param fp File pointer to the file.
 * @param position Position in the file to start extracting content.
 * @param line_count Pointer to the line counter.
 * @return Dynamically allocated string containing the macro content.
 */
char *extract_macro_content(FILE *fp, fpos_t *position, int *line_count);

/**
 * Validates a macro declaration.
 *
 * @param str String containing the macro declaration.
 * @param p_macro_name Pointer to store the macro name.
 * @param line_counter Line number of the macro declaration.
 * @param file_name Name of the file containing the macro declaration.
 * @return 1 if the macro declaration is valid, 0 otherwise.
 */
int is_macro_declaration_valid(char *str, char **p_macro_name, int line_counter, char *file_name);

/**
 * Collects all macros in a file into a linked list.
 *
 * @param file_name Name of the file to scan for macros.
 * @param macro_list_head Pointer to the head of the linked list of macros.
 * @return SUCCESS if macros were collected successfully, FAILURE otherwise.
 */
int collect_macros_to_linked_list(char *file_name, node **macro_list_head);

/**
 * Processes a macro declaration in a file.
 *
 * @param fp File pointer to the file.
 * @param line_counter Pointer to the line counter.
 * @param macro_list_head Pointer to the head of the linked list of macros.
 * @param file_name Name of the file containing the macro declaration.
 * @return SUCCESS if the macro was processed successfully, FAILURE otherwise.
 */
int process_macro_declaration(FILE *fp, int *line_counter, node **macro_list_head, char *file_name);

/**
 * Removes macro declarations from a file and saves the result in a temporary file.
 *
 * @param file_name Name of the file to filter macros from.
 * @return Name of the new file without the macros, or NULL on failure.
 */
int filter_macro_declarations(char file_name[]);

/**
 * Extracts parts of a line before and after a macro name.
 *
 * @param line The original line containing the macro name.
 * @param macro_name The macro name to extract around.
 * @param start_part Buffer to store the part before the macro name.
 * @param end_part Buffer to store the part after the macro name.
 */
void extract_line_parts(const char *line, const char *macro_name, char *start_part, char *end_part);

/**
 * Replaces a macro in a line with its content.
 *
 * @param line The original line containing the macro name.
 * @param macro Pointer to the macro node.
 * @return Dynamically allocated string with the macro content replaced, or NULL on failure.
 */
char *replace_macro_in_line(char *line, node *macro);

/**
 * Processes each line of a file and replaces macro calls with their content.
 *
 * @param input_file File pointer to the input file.
 * @param output_file File pointer to the output file.
 * @param macro Pointer to the macro node.
 * @return 1 if macros were processed successfully, 0 otherwise.
 */
int process_macros_in_file(FILE *input_file, FILE *output_file, node *macro);

/**
 * Replaces all macros in a file with their definitions and saves the result in a new file.
 *
 * @param file_name Name of the file to process.
 * @param head Pointer to the head of the linked list of macros.
 * @return Name of the new file with macros replaced, or NULL on failure.
 */
char *replace_all_macros_in_file(char file_name[], node *head);

/**
 * Processes macros in a file.
 *
 * @param file_name Name of the file to process.
 * @return 1 if macros were processed successfully, 0 otherwise.
 */
int process_macros(char file_name[]);

#endif /* PRE_ASSEMBLER_H */
