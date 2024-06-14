#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int occurences;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = malloc(sizeof(node));

    printf("Enter an int: ");

    scanf("%d", &(list->occurences));

    printf("Enter another int: ");

    list->next = malloc(sizeof(node));

    node *pos = list->next;

    scanf("%d", &(pos->occurences));

    pos = list;
    while (pos != NULL)
    {
        printf("%d\n", pos->occurences);
        pos = pos->next;
    }

    return 0;
}