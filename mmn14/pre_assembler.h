#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include <stdio.h>
#include "list_data_structure.h"

/**
 * Processes macros in a file with ".am" extention.
 * This function processes the input assembly source file in preparation for the main assembly process.
 * The pre-assembler typically handles tasks such as:
 * - Expanding macros: Replacing macro calls with their corresponding macro definitions.
 * - Removing comments: Stripping out comments to clean the source code.
 *
 * The output of this function is a cleaned and fully expanded version of the source file, ready for the assembler.
 *
 * @param file_name Name of the file to process.
 * @return 1 if macros were processed successfully, 0 otherwise.
 */
int pre_assembler(char file_name[]);

#endif /* PRE_ASSEMBLER_H */
