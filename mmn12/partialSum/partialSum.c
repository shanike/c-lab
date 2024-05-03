#include <stdio.h>
#include <stdlib.h>

int *mallocInts(int numberOfInts)
{
    return (int *)malloc(numberOfInts * sizeof(int));
}

/*
Returns an array in which each item from the original array is saved
in the returned array as the sum of all preceding items inclusive
*/
int *partialSums(int *array, int length)
{
    int i, pre_i, partial_sum = 0, *partial_sums_array = mallocInts(length);
    for (i = 0; i < length; i++)
    {
        partial_sum = *(array + i);
        for (pre_i = 0; pre_i < i; pre_i++)
        {
            partial_sum += *(array + pre_i);
        }
        *(partial_sums_array + i) = partial_sum;
    }
    return partial_sums_array;
}

/* Fills array with integers by scanning stdio */
void fillIntsStdio(int *array, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("Enter integer number %d: ", i + 1);
        scanf("%d", (array + i));
    }
}

void printArray(int *array, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%d ", *(array + i));
    }
    printf("\n");
}

int main()
{
    int length, *array_pointer, *partial_sums_array;

    printf("The size of the array is: ");
    scanf("%d", &length);

    array_pointer = mallocInts(length);
    fillIntsStdio(array_pointer, length);
    printf("The original array is: ");
    printArray(array_pointer, length);
    partial_sums_array = partialSums(array_pointer, length);
    printf("The partial-sums array is: ");
    printArray(partial_sums_array, length);
    return 0;
}
