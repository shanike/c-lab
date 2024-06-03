#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    /* TODO: Initialize to empty sets */
    SET SETA = {0} /* , SETB, SETC, SETD, SETE, SETF */;

    int ints[] = {1, 2, 3, 10, -1};
    char *input = malloc(1);
    char c;
    int i = 0;

    char *func;

    read_set(&SETA, ints);
    print_set(&SETA);


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
    if ("stop")
    {
        return 0;
    }
    return 0;
}
