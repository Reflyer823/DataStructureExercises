// 1003 Emergency
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 定义邻接表类型
typedef int Vertex;
typedef struct AdjaListStruct *AdjaList;
struct AdjaListStruct {
    Vertex V;
    int len;
    AdjaList next;
};

// 定义图类型
struct LGraphStruct {
    int Nv, Ne;
    AdjaList *edges;
    int *values;
};
typedef struct LGraphStruct *LGraph;
#define INFINITY 10000000

// 声明图类型函数
LGraph CreateGraph(int Nv);
void FreeGraph(LGraph G);
void AddEdge(LGraph G, Vertex V1, Vertex V2, int len);
void Dijkstra(LGraph G, Vertex S, Vertex D);

// 主函数
int main() {
    int N, M, S, D;
    int V1, V2, len;

    // 从输入中读取图
    scanf("%d %d %d %d", &N, &M, &S, &D);
    LGraph G = CreateGraph(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &G->values[i]);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &V1, &V2, &len);
        AddEdge(G, V1, V2, len);
    }

    // 对图执行Dijkstra算法
    Dijkstra(G, S, D);

    FreeGraph(G);
    return 0;
}

// 创建一个指定节点数的空图
LGraph CreateGraph(int Nv) {
    LGraph G = (LGraph)malloc(sizeof(struct LGraphStruct));
    G->Nv = Nv;
    G->Ne = 0;
    G->values = (int *)malloc(sizeof(int) * Nv);
    G->edges = (AdjaList *)malloc(sizeof(AdjaList) * Nv);
    for (int i = 0; i < G->Nv; i++)
        G->edges[i] = NULL;
    return G;
}

// 释放图的存储空间
void FreeGraph(LGraph G) {
    // 将每个节点的邻接表空间释放掉
    for (int i = 0; i < G->Nv; i++) {
        AdjaList L = G->edges[i], temp;
        while (L) {
            temp = L;
            L = L->next;
            free(temp);
        }
    }
    // 释放图结构的空间
    free(G->values);
    free(G->edges);
    free(G);
}

// 创建一个邻接表的新节点
AdjaList MakeAdjaListNode(Vertex V, int len, AdjaList next) {
    AdjaList new = (AdjaList)malloc(sizeof(struct AdjaListStruct));
    new->V     = V;
    new->len   = len;
    new->next  = next;
    return new;
}

// 在节点V1和V2之间添加一条边
void AddEdge(LGraph G, Vertex V1, Vertex V2, int len) {
    // 边数加一
    G->Ne++;
    // 在V1的邻接表中添加V2
    G->edges[V1] = MakeAdjaListNode(V2, len, G->edges[V1]);
    // 在V2的邻接表中添加V1
    G->edges[V2] = MakeAdjaListNode(V1, len, G->edges[V2]);
}

// Dijkstra算法计算从源点S到终点D的最短距离路径数以及最大节点值之和
void Dijkstra(LGraph G, Vertex S, Vertex D) {
    // 创建并初始化collected数组
    char *collected = (char *)malloc(sizeof(char) * G->Nv);
    memset(collected, 0, sizeof(char) * G->Nv);

    // 创建并初始化dist数组
    int *dist = (int *)malloc(sizeof(int) * G->Nv);
    for (int i = 0; i < G->Nv; i++) dist[i] = INFINITY;
    dist[S] = 0;

    // 创建并初始化paths数组，记录最短路径条数
    int *paths = (int *)malloc(sizeof(int) * G->Nv);
    memset(paths, 0, sizeof(int) * G->Nv);
    paths[S] = 1;

    // 创建并初始化maxSum数组，记录最短路径中最大的节点值和
    int *maxSum = (int *)malloc(sizeof(int) * G->Nv);
    memset(maxSum, 0, sizeof(int) * G->Nv);
    maxSum[S] = G->values[S];

    int V;
    while (1) {
        // 查找未收录节点中距离的最小值
        V = -1;
        for (int i = 0; i < G->Nv; i++) {
            if (!collected[i] && (V == -1 || dist[i] < dist[V]))
                V = i;
        }
        // 未找到或找到的是目标节点时则退出
        if (V == -1 || V == D) break;
        // 将V收录进来
        collected[V] = 1;
        // 检查V的每个邻接点的距离值是否需要更新
        for (AdjaList L = G->edges[V]; L; L = L->next) {
            // 只访问未收录节点
            if (!collected[L->V]) {
                // 距离更小，则更新距离、最短路径数和节点值和
                if (dist[V] + L->len < dist[L->V]) {
                    dist[L->V] = dist[V] + L->len;
                    paths[L->V] = paths[V];
                    maxSum[L->V] = maxSum[V] + G->values[L->V];
                } else if (dist[V] + L->len == dist[L->V]) {
                    // 距离相等则最短路径数加上当前节点的最短路径数
                    paths[L->V] += paths[V];
                    // 若当前路径的节点值之和更大，则更新
                    if (maxSum[V] + G->values[L->V] > maxSum[L->V])
                        maxSum[L->V] = maxSum[V] + G->values[L->V];
                }
            }
        }
    }

    // 输出结果
    printf("%d %d\n", paths[D], maxSum[D]);

    free(maxSum);
    free(paths);
    free(dist);
    free(collected);
}