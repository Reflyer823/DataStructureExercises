// 07-图4 哈利·波特的考试
#include <stdio.h>

#define INFINITY 10000

int main() {
    int N, M;
    int V1, V2, len;
    int D[100][100];

    // 读取点和边的个数并初始化图数组
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            D[i][j] = INFINITY;
        D[i][i] = 0;
    }

    // 从输入中读取各条边的长度
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &V1, &V2, &len);
        D[V1 - 1][V2 - 1] = len;
        D[V2 - 1][V1 - 1] = len;
    }

    // Floyd算法求最短路径矩阵D
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (D[i][k] + D[k][j] < D[i][j])
                    D[i][j] = D[i][k] + D[k][j];

    // 对每个动物，求最短路径中的最长
    int maxLen, minAni = -1, minAniLen = INFINITY;
    for (int i = 0; i < N; i++) {
        maxLen = -1;
        for (int j = 0; j < N; j++)
            if (D[i][j] > maxLen)
                maxLen = D[i][j];
        if (maxLen < minAniLen) {
            minAniLen = maxLen;
            minAni = i;
        }
    }

    // 输出结果
    if (minAni == -1) printf("0\n");
    else printf("%d %d\n", minAni + 1, minAniLen);

    return 0;
}