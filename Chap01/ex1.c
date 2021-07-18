#include <stdio.h>
#include <stdlib.h>

int main(){
    int K;
    scanf("%d\n", &K);
    int *s = (int *)malloc(sizeof(int) * K);

    for (int i = 0; i < K; i++) {
        scanf("%d", &s[i]);
    }

    int thisSum = 0, maxSum = 0;
    for (int i = 0; i < K; i++) {
        if (thisSum > 0) {
            thisSum += s[i];
        } else {
            thisSum = s[i];
        }
        if (thisSum > maxSum) {
            maxSum = thisSum;
        }
    }
    printf("%d", maxSum);

    free(s);
    return 0;
}