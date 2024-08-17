#ifndef OB_OUTPUT_H
#define OB_OUTPUT_H

#include "encoding.h"

/**
 * @brief Creates an output file with a .ob extension containing the assembled code's instructions and data.
 *
 * This function generates an object file (.ob) that contains the memory addresses and their corresponding values
 * for both instructions and data. The first line of the file contains the instruction count (IC) and data count (DC).
 * Each subsequent line contains a memory address and the corresponding word value, where the address is printed
 * in a 4-digit decimal format and the word value is printed in a 5-digit octal format.
 *
 * @param instructions A pointer to the head of a linked list containing the instructions to be written to the file.
 * @param data A pointer to the head of a linked list containing the data to be written to the file.
 * @param input_file_name The name of the input file (without extension) used to create the output file name.
 * @param IC The instruction count, representing the number of instructions.
 * @param DC The data count, representing the number of data entries.
 * @return int Returns SUCCESS (typically 0) if the file is created successfully; otherwise, returns FAILURE (typically -1).
 */
int create_ob_file(wordNode *instructions, wordNode *data, char *input_file_name, int IC, int DC);

#endif
