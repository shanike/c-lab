#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define NUM_OF_SETS 6
#define ERROR_UNDEF_COMMAND_NAME "Undefined command name"
#define ERROR_UNDEF_SET_NAME "Undefined set name"
#define ERROR_MISSING_COMMA "Missing comma"
#define ERROR_ILLEGAL_COMMA "Illegal comma"
#define ERROR_MEMBER_NOT_INT "Invalid set member - not an integer"
#define ERROR_MEMBER_OUT_OF_RANGE "Invalid set member - value out of range"
#define ERROR_ALLOC_MEM "Error allocating memory"

Command get_command(char *command);
int is_whitespace(int c);
int is_comma(int c);
int is_digit(int c);
void trim_str(char *str);
int get_command_end(char *line);
char *scan_line();

int get_arg1(char *arg1, char *line, int command_end_ndx)
{
    int i, j;
    printf(">get_arg1: command_end_ndx=%d\n", command_end_ndx);
    /* i = first non-whitespace */
    i = command_end_ndx + 1;
    while (line[i] != '\0' && is_whitespace(line[i]))
    {
        /* Ignore whitespace */
        i++;
    }
    /* j = first whitespace */
    j = i;
    while (!is_whitespace(line[j]) && !is_comma(line[j]) && line[j] != '\0')
    {
        j++;
    }
    strncpy(arg1, line + i, j - i);
    return j - 1;
}

int add_member(char *member_str, int *members, int members_len)
{
    printf(">add_member: member_str=%s\n", member_str);
    int num = atoi(member_str);
    if (num < 0 || num > 127)
    {
        printf("%s\n", ERROR_MEMBER_OUT_OF_RANGE);
        return 0;
    }
    members = realloc(members, (strlen(member_str) + 1) * sizeof(int));
    members[members_len] = num;
    return 1;
}

/*
Returns an array of integers, where the last member is -1.
Or NULL if there is an error.
Handles the error messages.
*/
int *get_members(char *line, int arg1_end_ndx)
{
    int i,
        /* Start by searching for comma before 1sh member */
        is_searching_for_comma = 1,
        *members = NULL,
        members_len = 0,
        member_begin_ndx = -1,
        member_end_ndx = -1,
        member_len = 0;
    char c,
        *member_str = NULL;

    printf(">get_members: arg1_end_ndx=%d\n", arg1_end_ndx);

    for (i = arg1_end_ndx + 1; line[i] != '\0'; i++)
    {
        c = line[i];
        printf(">i=%d, c=%c\n", i, c);
        if (is_searching_for_comma)
        {
            printf(">searching for comma");
            if (is_comma(c))
            {
                is_searching_for_comma = 0;
                continue;
            }

            /* Not comma and not whitespace -> ERROR */
            if (!is_whitespace(c))
            {
                printf("%s\n", ERROR_MISSING_COMMA);
                return NULL;
            }
        }
        else
        {
            printf(">searching for member");
            if (member_begin_ndx > -1)
            {
                if (!is_digit(c))
                {
                    /* Found end of member */
                    member_end_ndx = i - 1;
                    printf("member_begin_ndx=%d, member_end_ndx=%d\n", member_begin_ndx, member_end_ndx);
                    member_len = member_end_ndx - member_begin_ndx + 1;
                    add_member(strcpy(member_str, line + member_begin_ndx), members, members_len);
                    members_len++;
                }
            }
            else
            {
                /* Ignore whitespace */
                if (is_whitespace(c))

                {
                    continue;
                }
                /* Search for members */
                if (!is_digit(c))
                {
                    printf("%s\n", ERROR_MEMBER_NOT_INT);
                    return NULL;
                }
                member_begin_ndx = i;
            }
        }
    }

    /* Add the last member */
    if (member_begin_ndx > -1)
    {
        add_member(strcpy(member_str, line + member_begin_ndx), members, members_len);
        members_len++;
    }

    return (int[]){1, 2, 3, 4, 5, -1};
}

Set *set_by_name(Set *sets, char *name)
{
    int i;
    for (i = 0; i < NUM_OF_SETS; i++)
    {
        if (strcmp((sets[i]).name, name) == 0)
        {
            return &(sets[i]);
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    Set SETA = {0};
    Set SETB = {0};
    Set SETC = {0};
    Set SETD = {0};
    Set SETE = {0};
    Set SETF = {0};
    Set *set1;
    Set sets[NUM_OF_SETS];
    char *line, *command_str;
    int command_end_ndx, arg1_end_ndx;
    int *members;
    Command command;
    char arg1[MAX_SET_NAME];

    /* TODO: try adding the strings "" to init {0} */
    strcpy(SETA.name, "SETA");
    strcpy(SETB.name, "SETB");
    strcpy(SETC.name, "SETC");
    strcpy(SETD.name, "SETD");
    strcpy(SETE.name, "SETE");
    strcpy(SETF.name, "SETF");
    sets[0] = SETA;
    sets[1] = SETB;
    sets[2] = SETC;
    sets[3] = SETD;
    sets[4] = SETE;
    sets[5] = SETF;

    while (1)
    {
        printf("\nEnter command: \n");

        line = scan_line();
        /* printf("line=%s;\n", line); */

        if (strcmp(line, "stop") == 0)
        {
            break;
        }

        trim_str(line);

        if (strlen(line) == 0)
        {
            continue;
        }

        command_end_ndx = get_command_end(line);
        if (command_end_ndx < 0)
        {
            printf("%s\n", ERROR_UNDEF_COMMAND_NAME);
            continue;
        }
        command_str = malloc((command_end_ndx + 1) * sizeof(char));
        if (command_str == NULL)
        {
            printf("%s\n", ERROR_ALLOC_MEM);
            return 1;
        }
        strncpy(command_str, line, command_end_ndx + 1);

        command = get_command(command_str);
        free(command_str);

        if (command == -1)
        {
            printf("%s\n", ERROR_UNDEF_COMMAND_NAME);
            continue;
        }

        switch (command)
        {
        case READ_SET:
            arg1_end_ndx = get_arg1(arg1, line, command_end_ndx);
            if (arg1 == NULL)
            {
                printf("Error getting arg1\n");
            }
            printf(">arg1=%s\n", arg1);
            set1 = set_by_name(sets, arg1);
            if (set1 == NULL)
            {
                printf("%s\n", ERROR_UNDEF_SET_NAME);
                continue;
            }
            members = get_members(line, arg1_end_ndx);
            if (members == NULL)
            {
                continue;
            }
            read_set(set1, (int[]){1, 2, 3, 4, 5, -1});
            print_set(set1);
            break;
        default:
            break;
        }
    }

    /* TODO: input */
    /*      Might be an empty line (only white characters) */
    /*      \t and/or \s separate the command-name from the arguments */
    /*      Arguments are separated by a single comma */
    /*      Between arguments and commas can be any number of white characters */
    /*      No comma after last argument */
    /*      \t or \s can be preset before the command-name or after the last argument */
    /*      No characters (except white characters) after the last argument */
    /*      Command-name is lower-cased only */
    /*      Group names are upper-cased only */
    /* TODO: call functions */
    /* NOTICE: a set can be passed as multiple arguments to the same function */
    return 0;
}

/*
Returns an array of pointers to the sets.
Set *init_sets()
{
    Set SETA = {0};
    Set SETB = {0};
    Set SETC = {0};
    Set SETD = {0};
    Set SETE = {0};
    Set SETF = {0};
    // Init an array of sets
    Set *sets = malloc(NUM_OF_SETS * sizeof(Set));
    if (sets == NULL)
    {
        printf("%s\n",ERROR_ALLOC_MEM);
        return NULL;
    }
    sets[0] = {0};
    sets[1] = {0};
    sets[2] = {0};
    sets[3] = {0};
    sets[4] = {0};
    sets[5] = {0};
    return sets;
}
 */
int is_whitespace(int c)
{
    return c == ' ' || c == '\t';
}

int is_comma(int c)
{
    return c == ',';
}

int is_digit(int c)
{
    return c >= '0' && c <= '9';
}

void trim_str(char *str)
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (is_whitespace(str[begin]))
    {
        begin++;
    }

    while (is_whitespace(str[end]) && (end >= begin))
    {
        end--;
    }

    for (i = begin; i <= end; i++)
    {
        str[i - begin] = str[i];
    }

    str[i - begin] = '\0';
}

/*
Returns the index of the end of the command in `line`.
The command is first non-whitespace string in `line`.
If there's no whitespace at all, will returns -1.
*/
int get_command_end(char *line)
{
    int i;
    for (i = 0; i < strlen(line); i++)
    {
        if (is_whitespace(line[i]))
        {
            return i - 1;
        }
    }
    return -1;
}

char *scan_line()
{
    char c;
    int i = 0;
    char *line = malloc(1);

    if (line == NULL)
    {
        printf("%s\n", ERROR_ALLOC_MEM);
        return NULL;
    }

    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            break;
        }

        i++;
        line = (char *)realloc(line, (i + 1) * sizeof(char));
        if (line == NULL)
        {
            printf("%s\n", ERROR_ALLOC_MEM);
            return NULL;
        }
        line[i - 1] = c;
    }
    line[i] = '\0';
    return line;
}

/*
Returns the command name. If the command is invalid, returns -1.
*/
Command get_command(char *command)
{
    if (strcmp(command, "read_set") == 0)
    {
        return READ_SET;
    }
    else if (strcmp(command, "print_set") == 0)
    {
        return PRINT_SET;
    }
    else if (strcmp(command, "union_set") == 0)
    {
        return UNION_SET;
    }
    else if (strcmp(command, "intersect_set") == 0)
    {
        return INTERSECT_SET;
    }
    else if (strcmp(command, "sub_set") == 0)
    {
        return SUB_SET;
    }
    else if (strcmp(command, "symdiff_set") == 0)
    {
        return SYMDIFF_SET;
    }
    else
    {
        /* Invalid command */
        return -1;
    }
}
