// 06-图2 Saving James Bond - Easy Version
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int N, D;
struct Location {
    int x, y;
};
struct Location *nodes;
char *visited;

int dfs(int V);

int main() {
    scanf("%d %d", &N, &D);
    nodes = (struct Location *)malloc(sizeof(struct Location) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &nodes[i].x, &nodes[i].y);
    }
    visited = (char *)malloc(sizeof(char) * N);
    memset(visited, 0, sizeof(char) * N);

    int answer = 0;
    for (int i = 0; i < N; i++) {
        // 若从中心出发可以跳到第i个点上，则从第i个点开始DFS，成功时直接退出循环
        if (nodes[i].x * nodes[i].x + nodes[i].y * nodes[i].y <= (7.5 + D) * (7.5 + D)) {
            answer = dfs(i);
            if (answer) break;
        }
    }
    if (answer) printf("Yes");
    else printf("No");

    free(visited);
    free(nodes);
    return 0;
}

#define Square(X) ((X) * (X))
// 从第V个点出发进行DFS
int dfs(int V) {
    // 标记已访问过
    visited[V] = 1;
    // 若可以直接跳上岸，返回成功
    if (nodes[V].x >= 50 - D || nodes[V].x <= D - 50 || nodes[V].y >= 50 - D || nodes[V].y <= D - 50)
        return 1;
    // 对于所有未访问过且距离能跳到的点，一一尝试能否成功，若有能成功的直接返回
    for (int i = 0; i < N; i++) {
        if (!visited[i] && (Square(nodes[V].x - nodes[i].x) + Square(nodes[V].y - nodes[i].y) <= Square(D))) {
            if (dfs(i)) return 1;
        }
    }
    // 全部尝试完均不行，返回失败
    return 0;
}