#include <stdio.h>

#define maxC(a, b) (((a) > (b)) ? (a) : (b))
#define maxD(a, b) (a) > (b) ? (a) : (b)

int main() {
    int resultC, resultD;

    resultC = 1+maxC(9, 9);
    printf("Using maxC: Result = %d\n", resultC);  

    resultD = 1+maxD(9,9);
    printf("Using maxD: Result = %d\n", resultD);  

    return 0;
}

