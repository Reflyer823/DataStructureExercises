// 10-排序6 Sort with Swap(0, i)
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;

    // 读取输入
    scanf("%d", &N);
    int *P = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &P[i]);

    // 依次访问每个环
    int res = 0, start, p, temp, count;
    for (int i = 0; i < N; i++) {
        if (P[i] == i) continue;
        // 走过环的每个元素，并计数
        p = start = i;
        count = 0;
        do {
            temp = P[p];
            P[p] = p;
            p = temp;
            count++;
        } while (p != start);
        // 根据环的起点是否是0，分别累加需要交换的步数
        if (start == 0) res += count - 1;
        else res += count + 1;
    }

    // 打印结果
    printf("%d", res);

    free(P);
    return 0;
}