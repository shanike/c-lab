#include <stdio.h>
#include <string.h>

int suffix(char str[], char c)
{
    int i, j, num_of_matches = 0;
    int str_length = strlen(str);

    for (i = 0; i < str_length; i++)
    {
        if (str[i] == c)
        {
            num_of_matches++;
            for (j = i; j < str_length; j++)
            {
                printf("%c", str[j]);
            }
            printf("\n");
        }
    }

    return num_of_matches;
}

int main(int argc, char const *argv[])
{
    char c;
    char str[127 + 1];
    int num_of_matches;

    printf("Enter a char and a string: ");
    scanf("%c %s", &c, str);
    printf("Got char: %c and string: %s\n", c, str);

    printf("Suffixes are: \n");
    num_of_matches = suffix(str, c);

    printf("Number of suffix matches: %d\n", num_of_matches);

    return 0;
}
