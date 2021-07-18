// 02-线性结构3 Reversing Linked List 
#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode {
    int addr;
    int data;
    int nextAddr;
    int nextIndex;
};

int main() {
    int firstAddr, N, K, firstIndex = -1;
    // 读取输入，存入数组中
    scanf("%d %d %d\n", &firstAddr, &N, &K);
    struct LinkedListNode *L = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &L[i].addr, &L[i].data, &L[i].nextAddr);
        L[i].nextIndex = -1;
    }
    // 寻找首元素位置
    for (int i = 0; i < N; i++) {
        if (L[i].addr == firstAddr) {
            firstIndex = i;
            break;
        }
    }
    // 寻找每个节点的后继节点下标
    for (int i = 0; i < N; i++) {
        if (L[i].nextAddr == -1) continue;
        for (int j = 0; j < N; j++) {
            if (L[j].addr == L[i].nextAddr) {
                L[i].nextIndex = j;
                break;
            }
        }
    }

    // 每K个逆向输出
    int currentIndex = firstIndex, flag = 1, lki = 0;
    int *LK = (int *)malloc(sizeof(int) * K);
    while (currentIndex != -1) {
        LK[lki++] = currentIndex;
        currentIndex = L[currentIndex].nextIndex;
        if (lki == K) {
            lki = 0;
            for (int i = K - 1; i >= 0; i--) {
                if (flag) {
                    printf("%05d %d ", L[LK[i]].addr, L[LK[i]].data);
                    flag = 0;
                } else printf("%05d\n%05d %d ", L[LK[i]].addr, L[LK[i]].addr, L[LK[i]].data);
            }
        }
    }
    // 将剩余不满K个元素原序输出
    for (int i = 0; i < lki; i++) {
        if (flag) {
            printf("%05d %d ", L[LK[i]].addr, L[LK[i]].data);
            flag = 0;
        } else printf("%05d\n%05d %d ", L[LK[i]].addr, L[LK[i]].addr, L[LK[i]].data);
    }
    printf("-1\n");

    free(LK);
    free(L);
    return 0;
}