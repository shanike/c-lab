#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

/* Macro declarations */
#define MACRO_DECLARATION "macr"
#define MACRO_END "endmacr"

/* TODO: why is 81 and not 80? */
/* Maximum length of a single command line */
#define MAX_LINE_LENGTH 81

/* Success and failure codes */
#define SUCCESS 1
#define FAILURE 0


#define INSTRUCTIONS_NUMBER 4
#define OP_CODES_NUMBER 16
#define REGISTERS_NUMBER 8

typedef struct location_in_file {
    char *file_name;
    int line_number;
} location_in_file;

#endif /* GLOBAL_VARIABLES_H */
