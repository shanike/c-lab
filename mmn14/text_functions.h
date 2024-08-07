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
 * Trims a specific character from the beginning and end of a string.
 *
 * This function removes a specific character from the beginning and end of a string.
 *
 * @param str The string to process.
 * @param c The character to remove.
 */
void trim_char(char *str, char c);

/**
 * Trims quotes from the beginning and end of a string.
 *
 * This function removes double quotes from the beginning and end of a string.
 *
 * @param str The string to process.
 */
void trim_quotes(char *str);

/**
 * Trims newline characters from the beginning and end of a string.
 *
 * This function removes newline characters from the beginning and end of a string.
 *
 * @param str The string to process.
 */
void trim_newlines(char *str);

#endif /* TEXT_FUNCTIONS_H */
