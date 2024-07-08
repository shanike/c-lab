#include <stdio.h>

#define maxC(a, b) (((a) > (b)) ? (a) : (b))
#define maxD(a, b) (a) > (b) ? (a) : (b)

int main() {
    int x = 2, y = 3;
    int resultC, resultD;

    resultC = maxC(1, 2) * maxC(3, 4);
    printf("Using maxC: Result = %d\n", resultC); 

    resultD = maxD(1, 2) * maxD(3, 4);
    printf("Using maxD: Result = %d\n", resultD);  

    return 0;
}

