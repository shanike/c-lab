#include <stdio.h>
#include <stdlib.h>

#define MAX 29

typedef struct NodeType
{
    int occurences;
    char *filename;
    struct NodeType *next;
} NodeType;

typedef NodeType *PNodeType;

void insert_number(int number, char *filename, PNodeType *arr)
{
    PNodeType curr_node = arr[number], prev_node = NULL;
    while (curr_node != NULL && curr_node->filename != filename)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if (curr_node == NULL)
    {
        curr_node = (NodeType *)malloc(sizeof(NodeType));
        curr_node->occurences = 1;
        curr_node->filename = filename;
        curr_node->next = NULL;
        if (prev_node != NULL)
        {
            prev_node->next = curr_node;
        }
        else
        {
            arr[number] = curr_node;
        }
    }
    else
    {
        curr_node->occurences++;
    }
}

void read_file(char *filename, PNodeType *arr)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        perror("Error opening file");
        exit(1);
    }

    char word[2];
    while (fscanf(file, "%s", word) != EOF)
    {
        insert_number(atoi(word), filename, arr);
    }

    fclose(file);
}

void print_nodelist(int number, PNodeType node)
{
    int node_index = 0;
    while (node != NULL)
    {
        if (node_index == 0)
        {
            printf("%d appears in ", number);
        }
        else
        {
            printf(", ");
        }
        printf("file %s - %d times", node->filename, node->occurences);
        node = node->next;
        node_index++;
    }
}

void print_array(PNodeType *arr)
{
    int num = 0;
    for (num = 0; num < MAX; num++)
    {
        print_nodelist(arr[num], num);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    PNodeType arr[MAX];
    int i;
    /* Initialize array to `NULL`s */
    for (i = 0; i < MAX; i++)
    {
        arr[i] = NULL;
    }

    for (i = 1; i < argc; ++i)
    {
        read_file(argv[i], arr);
    }

    print_array(arr);

    return 0;
}