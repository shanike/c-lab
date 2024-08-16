#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#define IS_DEBUG 0
#define IS_DEBUG_FIRST_PASS 0
#define IS_DEBUG_ENCODING 0
#define IS_DEBUG_SECOND_PASS 0

/* Macro declarations */
#define MACRO_DECLARATION "macr"
#define MACRO_END "endmacr"

/* Maximum length of a single command line */
#define MAX_LINE_LENGTH 80
/* Maximum length of a label */
#define MAX_LABEL_LENGTH 31

/* Success and failure codes */
#define SUCCESS 1
#define FAILURE 0

#define DIRECTIVES_NUMBER 4
#define OPERATIONS_NUMBER 16
#define REGISTERS_NUMBER 8

#define DIRECTIVE_DATA ".data"
#define DIRECTIVE_STRING ".string"
#define DIRECTIVE_ENTRY ".entry"
#define DIRECTIVE_EXTERN ".extern"

#define INLINE_WHITESPACE " \t"

#define OBJECT_FILE_EXT ".ob"
#define ASSEMBLY_FILE_EXT ".as"
#define AFTER_MACRO_FILE_EXT ".am"
#define ENTRY_FILE_EXT ".ent"
#define EXTERN_FILE_EXT ".ext"

#define BITS_IN_WORD 15

#define MAX_ARGS_NUMBER 2

#define INSTRUCTIONS_MEMORY_ADDRESS_START 100 /* The memory address where the instructions start */

typedef struct location_in_file
{
    char *file_name;
    int line_number;
} location_in_file;

#endif /* GLOBAL_VARIABLES_H */
