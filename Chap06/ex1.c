// 06-图1 列出连通集
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 定义图类型
int Nv, Ne;
int *G;
char *visited;
#define G(V, W) G[(V) * Nv + (W)]

// 队列类型定义
struct QueueNode {
    int *elements;
    int first;
    int last;
    int N;
    int nums;
};
typedef struct QueueNode *Queue;
Queue q;

// 队列函数声明
Queue CreatQueue(int N);
void FreeQueue(Queue q);
int AddQueue(Queue q, int x);
int DeleteQueue(Queue q, int *x);
int QueueLength(Queue q);

// 图函数声明
void dfs(int V);
void bfs(int V);

int main() {
    int V1, V2;

    scanf("%d %d", &Nv, &Ne);
    G = (int *)malloc(sizeof(int) * Nv * Nv);
    memset(G, 0, sizeof(int) * Nv * Nv);
    visited = (char *)malloc(sizeof(char) * Nv);
    for (int i = 0; i < Ne; i++) {
        scanf("%d %d", &V1, &V2);
        G(V1, V2) = 1;
        G(V2, V1) = 1;
    }

    memset(visited, 0, sizeof(char) * Nv);
    for (int V = 0; V < Nv; V++) {
        if (!visited[V]) {
            printf("{ ");
            dfs(V);
            printf("}\n");
        }
    }

    memset(visited, 0, sizeof(char) * Nv);
    q = CreatQueue(Nv);
    for (int V = 0; V < Nv; V++) {
        if (!visited[V]) {
            printf("{ ");
            bfs(V);
            printf("}\n");
        }
    }

    FreeQueue(q);
    free(G);
    free(visited);
    return 0;
}

// 从节点V开始深度优先遍历图
void dfs(int V) {
    visited[V] = 1;
    printf("%d ", V);
    for (int W = 0; W < Nv; W++) {
        if (!visited[W] && G(V, W))
            dfs(W);
    }
}

// 从节点V开始广度优先遍历图
void bfs(int V) {
    int W;
    visited[V] = 1;
    printf("%d ", V);
    AddQueue(q, V);
    while (DeleteQueue(q, &W) == 0) {
        for (int X = 0; X < Nv; X++) {
            if (!visited[X] && G(W, X)) {
                visited[X] = 1;
                printf("%d ", X);
                AddQueue(q, X);
            }
        }
    }
}

// 创建一个容量为N的队列
Queue CreatQueue(int N) {
    Queue q = (Queue)malloc(sizeof(struct QueueNode));
    q->elements = (int *)malloc(sizeof(int) * N);
    q->first = N - 1;
    q->last = N - 1;
    q->N = N;
    q->nums = 0;
    return q;
}

// 释放队列存储空间
void FreeQueue(Queue q) {
    free(q->elements);
    free(q);
}

// 队列q添加一个元素x，返回0成功，返回-1失败
int AddQueue(Queue q, int x) {
    if (q->nums == q->N) return -1;
    q->last = (q->last + 1) % q->N;
    q->elements[q->last] = x;
    q->nums++;
    return 0;
}

// 队列q删除一个元素并赋值给*x，返回0成功，返回-1失败
int DeleteQueue(Queue q, int *x) {
    if (q->nums == 0) return -1;
    q->first = (q->first + 1) % q->N;
    *x = q->elements[q->first];
    q->nums--;
    return 0;
}

// 返回队列内元素个数
int QueueLength(Queue q) {
    return (q->nums);
}