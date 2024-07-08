#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80

void read_file(char filename[])
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    int i = 0;

    printf("DEBUG: filename = %s\n", filename);

    if (!file)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        printf("line %d: %s", i, line);
        i++;
    }
    free(line);
    fclose(file);
}
