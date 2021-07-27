// 05-树8 File Transfer
#include <stdio.h>
#include <stdlib.h>

int GetRoot(int *set, int n) {
    while (set[n] >= 0)
        n = set[n];
    return n;
}

int min(int x, int y) {
    return (x < y ? x : y);
}

int main() {
    int N, n1, n2, p1, p2;
    char c;
    int *set;

    scanf("%d", &N);
    set = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) set[i] = -1;
    while (1) {
        scanf("\n%c", &c);
        if (c == 'S') break;
        scanf(" %d %d", &n1, &n2);
        p1 = GetRoot(set, n1 - 1);
        p2 = GetRoot(set, n2 - 1);
        // 检查两个节点是否已经联通，不联通则将集合相并
        if (c == 'I' && p1 != p2) {
            // 确保p1的值是较小的，也就是层数高的
            if (set[p1] > set[p2]) {
                int temp = p1;
                p1 = p2;
                p2 = temp;
            }
            // 更新p1的层数
            set[p1] = min(set[p1], set[p2] - 1);
            // 将p2挂在p1下
            set[p2] = p1;
        } else if (c == 'C') {
            if (p1 == p2) printf("yes\n");
            else printf("no\n");
        }
    }
    int num = 0;
    for (int i = 0; i < N; i++)
        if (set[i] < 0) num++;
    if (num == 1) printf("The network is connected.\n");
    else printf("There are %d components.\n", num);

    free(set);
    return 0;
}