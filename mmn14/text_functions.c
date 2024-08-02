#include <stdio.h>
#include <ctype.h>
#include <string.h>

void remove_spaces_next_to_comma(char *str)
{
    /* New pointer to the str*/
    char *ptr = str;

    if (*ptr == ',')
        return;

    while ((ptr = strchr(ptr, ',')) != NULL)
    {
        /* Check if there is a space before the comma */
        if (ptr > str && *(ptr - 1) == ' ')
        {
            /* Remove the space before the comma */
            memmove(ptr - 1, ptr, strlen(ptr) + 1);
            /* After removing the space, check if there is also a space right after the comma */
            if (*(ptr) == ' ')
            {
                /* Remove the space after the comma */
                memmove(ptr, ptr + 1, strlen(ptr));
            }
        }
        /* Check if there is a space after the comma (and not already handled above) */
        else if (*(ptr + 1) == ' ')
        {
            memmove(ptr + 1, ptr + 2, strlen(ptr + 2) + 1); /* Remove the space after the comma */
        }

        /* Move to the next character after the comma */
        ptr++;
    }
}

/* Check if the char is a space or a tab */
int is_white_space_or_tab(char c)
{
    return (isspace(c) && c != '\n');
}
