#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

/* Debug flags */
#define IS_DEBUG 1
#define IS_DEBUG_FIRST_PASS 1
#define IS_DEBUG_ENCODING 1
#define IS_DEBUG_SECOND_PASS 1

/* Macro declarations */
#define MACRO_DECLARATION "macr"
#define MACRO_END "endmacr"

#define MAX_LINE_LENGTH 81  /* Maximum length of a single command line */
#define MAX_LABEL_LENGTH 31 /* Maximum length of a label */

/* Success and failure codes */
#define SUCCESS 1
#define FAILURE 0

#define DIRECTIVES_NUMBER 4  /* Number of directives */
#define OPERATIONS_NUMBER 16 /* Number of operations */
#define REGISTERS_NUMBER 8   /* Number of registers */

/* Directives */
#define DIRECTIVE_DATA ".data"
#define DIRECTIVE_STRING ".string"
#define DIRECTIVE_ENTRY ".entry"
#define DIRECTIVE_EXTERN ".extern"

#define INLINE_WHITESPACE " \t"

/* File extensions */
#define OBJECT_FILE_EXT ".ob"
#define ASSEMBLY_FILE_EXT ".as"
#define AFTER_MACRO_FILE_EXT ".am"
#define ENTRY_FILE_EXT ".ent"
#define EXTERN_FILE_EXT ".ext"

#define BITS_IN_WORD 15

#define MAX_ARGS_NUMBER 2

#define MAX_IMMEDIATE_VALUE 2047
#define MIN_IMMEDIATE_VALUE -2048

/* Memory */
#define INSTRUCTIONS_MEMORY_ADDRESS_START 100 /* The memory address where the instructions start */
#define MEMORY_SIZE 4096                      /* The maximum memory size */

/* Chars */
#define COMMA ','
#define COLON ':'
#define SPACE ' '
#define TAB '\t'

typedef struct location_in_file
{
    char *file_name;
    int line_number;
} location_in_file;

typedef unsigned short int word;

#endif /* GLOBAL_VARIABLES_H */
