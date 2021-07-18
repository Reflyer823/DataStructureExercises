// 02-线性结构3 Reversing Linked List 
#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode {
    int data;
    int nextAddr;
};

int main() {
    int firstAddr, N, K, currentAddr;
    struct LinkedListNode L[100000];
    // 读取输入，存入数组中
    scanf("%d %d %d\n", &firstAddr, &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &currentAddr);
        scanf("%d %d", &L[currentAddr].data, &L[currentAddr].nextAddr);
    }

    // 每K个逆向输出
    int flag = 1, lki = 0;
    int *LK = (int *)malloc(sizeof(int) * K);
    currentAddr = firstAddr;
    while (currentAddr != -1) {
        LK[lki++] = currentAddr;
        currentAddr = L[currentAddr].nextAddr;
        if (lki == K) {
            lki = 0;
            for (int i = K - 1; i >= 0; i--) {
                if (flag) {
                    printf("%05d %d ", LK[i], L[LK[i]].data);
                    flag = 0;
                } else printf("%05d\n%05d %d ", LK[i], LK[i], L[LK[i]].data);
            }
        }
    }
    // 将剩余不满K个元素原序输出
    for (int i = 0; i < lki; i++) {
        if (flag) {
            printf("%05d %d ", LK[i], L[LK[i]].data);
            flag = 0;
        } else printf("%05d\n%05d %d ", LK[i], LK[i], L[LK[i]].data);
    }
    printf("-1\n");

    free(LK);
    return 0;
}