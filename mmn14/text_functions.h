#ifndef TEXT_FUNCTIONS_H
#define TEXT_FUNCTIONS_H

/**
 * Removes spaces adjacent to commas in a string.
 *
 * This function iterates through the string, and for each comma, it removes
 * any spaces that are immediately before or after the comma.
 *
 * @param str The string to process.
 */
void remove_spaces_next_to_comma(char *str);

/**
 * Checks if a character is a space or a tab.
 *
 * This function determines if the given character is a space (' ') or a tab ('\t').
 * It excludes newline characters ('\n') from being considered as spaces or tabs.
 *
 * @param c The character to check.
 * @return 1 if the character is a space or a tab, 0 otherwise.
 */
int is_white_space_or_tab(char c);

/**
 * Extracts the string value from a given .string directive.
 *
 * This function extracts a string, which is enclosed in double quotes. 
 * The extracted string is stored in the result parameter.
 * 
 * If the input string is not enclosed in double quotes, an error message is printed.
 *
 * @param input The .string directive.
 * @param result Pointer to the extracted string.
 * @param curr_location The location in the file where the input string is located.
 */
void extract_data_string(char *input, char **result, location_in_file curr_location);

#endif /* TEXT_FUNCTIONS_H */
