#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define NUM_OF_SETS 6
#define INVALID_MEMBER -999
#define ARG_ERROR -999
#define SCAN_ERROR -999

#define ERROR_UNDEF_COMMAND_NAME "\nUndefined command name"
#define ERROR_UNDEF_SET_NAME "\nUndefined set name"
#define ERROR_MISSING_COMMA "\nMissing comma"
#define ERROR_ILLEGAL_COMMA "\nIllegal comma"
#define ERROR_MEMBER_NOT_INT "\nInvalid set member - not an integer"
#define ERROR_MEMBER_OUT_OF_RANGE "\nInvalid set member - value out of range"
#define ERROR_MEMBER_NOT_TERMINATED "\nList of set members is not terminated correctly"
#define ERROR_PARAM_MISSING "\nMissing parameter"
#define ERROR_PARAM_EXTRA "\nExtraneous text after end of command"
#define ERROR_PARAM_MISSING "\nMissing parameter"
#define ERROR_ALLOC_MEM "\nError allocating memory"

Command get_command(char *command);
int is_whitespace(int c);
int is_comma(int c);
int is_digit(int c);
int is_valid_int(char *str);
int has_only_zeroes(char *str);
int has_only_whitespaces(char *str, int from);
void trim_str(char *str);
int get_command_end(char *line);
int scan_line(char **line);
Set *set_by_name(Set *sets, char *name);

int get_arg1_ndx(char *arg1, char *line, int command_end_ndx)
{
    int i, j;
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

char *append_char(char *str, int str_len, char c)
{
    str = realloc(str, (str_len + 1) * sizeof(char));
    if (str == NULL)
    {
        printf("%s\n", ERROR_ALLOC_MEM);
        return NULL;
    }
    str[str_len] = c;
    return str;
}

/*
Returns a valid in-range (0-127) int, or INVALID_MEMBER (-999) if invalid.
Handles error messages.
*/
int convert_member(char *member_str)
{
    int member;

    if (!is_valid_int(member_str))
    {
        printf("%s\n", ERROR_MEMBER_NOT_INT);
        return 0;
    }
    member = atoi(member_str);
    if (member == 0)
    {
        /* atoi will return 0 also for 0 and also for invalid */
        if (!has_only_zeroes(member_str))
        {
            printf("%s\n", ERROR_MEMBER_NOT_INT);
            return 0;
        }
    }
    if ((member < 0 || member > 127) && member != -1)
    {
        printf("%s\n", ERROR_MEMBER_OUT_OF_RANGE);
        return INVALID_MEMBER;
    }
    return member;
}

/*
Returns an array of integers, where the last member is -1.
Or NULL if there is an error.
Handles the error messages.
*/
int *get_members(char *line, int arg1_end_ndx)
{
    int i,
        /* Start by searching for comma before 1st member */
        is_searching_for_comma = 1,
        *members = NULL,
        members_len = 0,
        member,
        member_len = 0;

    char c, next_c,
        *member_str = NULL;

    for (i = arg1_end_ndx + 1; line[i] != '\0'; i++)
    {
        c = line[i];
        if (is_searching_for_comma)
        {
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
            /* Ignore whitespace */
            if (is_whitespace(c))
            {
                continue;
            }
            if (is_comma(c))
            {
                printf("%s\n", ERROR_ILLEGAL_COMMA);
                return NULL;
            }

            /* Not whitespace and not comma -> add to member_str */
            member_str = append_char(member_str, member_len, c);
            member_len++;

            /* If next character is whitespace or comma, add member_str */
            next_c = line[i + 1];
            if (is_comma(next_c) || is_whitespace(next_c) || next_c == '\0')
            {
                member_str = append_char(member_str, member_len, '\0');
                member_len++;

                member = convert_member(member_str);
                if (member == -999)
                {
                    return NULL;
                }
                if (member == -1 && !has_only_whitespaces(line, i + 1))
                {
                    printf("%s\n", ERROR_MEMBER_NOT_TERMINATED);
                    return NULL;
                }

                members = realloc(members, (members_len + 1) * sizeof(int));
                if (members == NULL)
                {
                    printf("%s\n", ERROR_ALLOC_MEM);
                    return NULL;
                }
                members_len++;
                members[members_len - 1] = member;

                /* Reset for next member */
                member_len = 0;
                member_str = NULL;
                member = INVALID_MEMBER;
                is_searching_for_comma = 1;
            }
        }
    }

    if (members[members_len - 1] != -1)
    {
        printf("%s\n", ERROR_MEMBER_NOT_TERMINATED);
        return NULL;
    }

    return members;
}

int get_next_args(char **args, char *line, int arg1_end_ndx, int expected /* disable using -1 */)
{
    int i,
        /* Start by searching for comma before 1st arg */
        is_searching_for_comma = 1,
        args_len = 0,
        arg_len = 0;

    char c, next_c,
        *arg = NULL;

    for (i = arg1_end_ndx + 1; line[i] != '\0'; i++)
    {
        c = line[i];
        if (is_searching_for_comma)
        {
            if (is_comma(c))
            {
                is_searching_for_comma = 0;
                continue;
            }

            /* Not comma and not whitespace -> ERROR */
            if (!is_whitespace(c))
            {
                printf("%s\n", ERROR_MISSING_COMMA);
                return ARG_ERROR;
            }
        }
        else
        {
            /* Ignore whitespace */
            if (is_whitespace(c))
            {
                continue;
            }
            if (is_comma(c))
            {
                printf("%s\n", ERROR_ILLEGAL_COMMA);
                return ARG_ERROR;
            }

            /* Not whitespace and not comma -> add to arg */
            arg = append_char(arg, arg_len, c);
            arg_len++;

            /* If next character is whitespace or comma, add arg */
            next_c = line[i + 1];
            if (is_comma(next_c) || is_whitespace(next_c) || next_c == '\0')
            {
                if (expected != -1 && args_len + 1 > expected)
                {
                    /* Don't add & ERROR */
                    printf("%s\n", ERROR_PARAM_EXTRA);
                    return ARG_ERROR;
                }

                arg = append_char(arg, arg_len, '\0');
                arg_len++;

                args = realloc(args, (args_len + 1) * sizeof(int));
                if (args == NULL)
                {
                    printf("%s\n", ERROR_ALLOC_MEM);
                    return ARG_ERROR;
                }
                args_len++;
                args[args_len - 1] = arg;

                /* Reset for next member */
                arg_len = 0;
                arg = NULL;
                is_searching_for_comma = 1;
            }
        }
    }
    if (expected != -1 && args_len < expected)
    {
        /* Never found but expected to -> ERROR*/
        printf("%s\n", ERROR_PARAM_MISSING);
        return ARG_ERROR;
    }
    printf("get_next_args: returning %d\n", args_len);
    return args_len;
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
    char
        *line = malloc(0),
        *command_str,
        arg1[MAX_SET_NAME],
        **next_args_str = malloc(0);
    int scan_result,
        command_end_ndx,
        arg1_end_ndx,
        next_args_count = 0,
        *members;
    Command command;
    Set **args_set = malloc(2 * sizeof(Command));

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
        if (line == NULL || args_set == NULL || next_args_str == NULL)
        {
            printf("%s\n", ERROR_ALLOC_MEM);
            break;
        }

        printf("\nEnter command and arguments: \n");

        scan_result = scan_line(&line);
        if (scan_result == EOF || strcmp(line, "stop") == 0 || scan_result == SCAN_ERROR)
        {
            break;
        }

        trim_str(line);

        if (strlen(line) == 0)
        {
            continue;
        }

        printf("Received: %s\n", line);

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
            continue;
        }
        strncpy(command_str, line, command_end_ndx + 1);

        command = get_command(command_str);
        free(command_str);

        if (command == -1)
        {
            printf("%s\n", ERROR_UNDEF_COMMAND_NAME);
            continue;
        }

        arg1_end_ndx = get_arg1_ndx(arg1, line, command_end_ndx);
        if (arg1 == NULL)
        {
            printf("Error getting arg1\n");
            continue;
        }

        set1 = set_by_name(sets, arg1);
        if (set1 == NULL)
        {
            printf("%s\n", ERROR_UNDEF_SET_NAME);
            continue;
        }

        if (command == READ_SET)
        {
            /* TODO: use next_args_str instead */
            members = get_members(line, arg1_end_ndx);
            if (members == NULL)
            {
                continue;
            }
            read_set(set1, members);
        }
        else if (command == PRINT_SET)
        {
            if (!has_only_whitespaces(line, arg1_end_ndx + 1))
            {
                printf("%s\n", ERROR_PARAM_EXTRA);
                continue;
            }
            print_set(set1);
        }
        else
        {
            next_args_count = get_next_args(next_args_str, line, arg1_end_ndx, 2);
            if (next_args_count == ARG_ERROR || next_args_str == NULL)
            {
                continue;
            }
            args_set[0] = set_by_name(sets, next_args_str[0]);
            args_set[1] = set_by_name(sets, next_args_str[1]);

            switch (command)
            {
            case UNION_SET:
                union_set(set1, args_set[0], args_set[1]);
                break;
            case INTERSECT_SET:
                intersect_set(set1, args_set[0], args_set[1]);
                break;
            case SUB_SET:
                sub_set(set1, args_set[0], args_set[1]);
                break;
            case SYMDIFF_SET:
                symdiff_set(set1, args_set[0], args_set[1]);
                break;
            default:
                break;
            }
        }
    }

    free(line);
    free(next_args_str);
    free(args_set);

    return 0;
}

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

int is_valid_int(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (!is_digit(str[i]) && str[i] != '-')
        {
            return 0;
        }
    }
    return 1;
}

int has_only_zeroes(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] != '0')
        {
            return 0;
        }
    }
    return 1;
}

int has_only_whitespaces(char *str, int from)
{
    int i;
    for (i = from; i < strlen(str); i++)
    {
        if (!is_whitespace(str[i]))
        {
            return 0;
        }
    }
    return 1;
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

int scan_line(char **line)
{
    char c;
    int i = 0, is_eof = 0;

    if (*line == NULL)
    {
        return SCAN_ERROR;
    }

    while (1)
    {
        c = getchar();
        if (c == '\n')
        {
            break;
        }
        if (c == EOF)
        {
            is_eof = 1;
            break;
        }

        i++;
        *line = (char *)realloc(*line, (i + 1) * sizeof(char));
        if (*line == NULL)
        {
            printf("%s\n", ERROR_ALLOC_MEM);
            return SCAN_ERROR;
        }
        (*line)[i - 1] = c;
    }
    (*line)[i] = '\0';
    return is_eof ? EOF : 1;
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
