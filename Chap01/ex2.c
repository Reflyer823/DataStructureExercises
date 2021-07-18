#include <stdio.h>
#include <stdlib.h>

int main(){
    int K;
    scanf("%d\n", &K);
    int *s = (int *)malloc(sizeof(int) * K);

    for (int i = 0; i < K; i++) {
        scanf("%d", &s[i]);
    }

    // 将两个和值都初始化为第一个元素的值
    int thisSum = s[0], maxSum = s[0];
    int thisLeft = 0, thisRight = 0;
    int maxLeft = 0, maxRight = 0;
    for (int i = 1; i < K; i++) {
        // 注意此处需要大于等于0，否则在最大和前面有一段0时，不会选择最小的起始下标
        if (thisSum >= 0) {
            thisSum += s[i];
            thisRight = i;
        } else {
            thisSum = s[i];
            thisLeft = thisRight = i;
        }
        if (thisSum > maxSum) {
            maxSum = thisSum;
            maxLeft = thisLeft;
            maxRight = thisRight;
        }
    }
    // 当最大和小于0时，需要特殊处理
    if (maxSum < 0) {
        maxSum = 0;
        maxLeft = 0;
        maxRight = K - 1;
    }
    printf("%d %d %d", maxSum, s[maxLeft], s[maxRight]);

    free(s);
    return 0;
}