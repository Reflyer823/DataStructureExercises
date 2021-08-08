// 07-图6 旅游规划
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 定义邻接表类型
typedef int Vertex;
typedef struct AdjaListStruct *AdjaList;
struct AdjaListStruct {
    Vertex V;
    int len, price;
    AdjaList next;
};

// 定义图类型
struct LGraphStruct {
    int Nv, Ne;
    AdjaList *edges;
};
typedef struct LGraphStruct *LGraph;
#define INFINITY 10000000

// 声明图类型函数
LGraph CreateGraph(int Nv);
void FreeGraph(LGraph G);
void AddEdge(LGraph G, Vertex V1, Vertex V2, int len, int price);
void Dijkstra(LGraph G, Vertex S, Vertex D);

// 主函数
int main() {
    int N, M, S, D;
    int V1, V2, len, price;

    // 从输入中读取图
    scanf("%d %d %d %d", &N, &M, &S, &D);
    LGraph G = CreateGraph(N);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &V1, &V2, &len, &price);
        AddEdge(G, V1, V2, len, price);
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
    free(G->edges);
    free(G);
}

// 创建一个邻接表的新节点
AdjaList MakeAdjaListNode(Vertex V, int len, int price, AdjaList next) {
    AdjaList new = (AdjaList)malloc(sizeof(struct AdjaListStruct));
    new->V      = V;
    new->len    = len;
    new ->price = price;
    new->next   = next;
    return new;
}

// 在节点V1和V2之间添加一条边
void AddEdge(LGraph G, Vertex V1, Vertex V2, int len, int price) {
    // 边数加一
    G->Ne++;
    // 在V1的邻接表中添加V2
    G->edges[V1] = MakeAdjaListNode(V2, len, price, G->edges[V1]);
    // 在V2的邻接表中添加V1
    G->edges[V2] = MakeAdjaListNode(V1, len, price, G->edges[V2]);
}

// Dijkstra算法计算从源点S到终点D的最短距离并输出
void Dijkstra(LGraph G, Vertex S, Vertex D) {
    // 创建并初始化collected数组
    char *collected = (char *)malloc(sizeof(char) * G->Nv);
    memset(collected, 0, sizeof(char) * G->Nv);
    collected[S] = 1;

    // 创建并初始化dist数组
    int *dist = (int *)malloc(sizeof(int) * G->Nv);
    for (int i = 0; i < G->Nv; i++) dist[i] = INFINITY;
    for (AdjaList L = G->edges[S]; L; L = L->next) dist[L->V] = L->len;
    dist[S] = 0;

    // 创建并初始化price数组
    int *price = (int *)malloc(sizeof(int) * G->Nv);
    for (int i = 0; i < G->Nv; i++) price[i] = 0;
    for (AdjaList L = G->edges[S]; L; L = L->next) price[L->V] = L->price;
    price[S] = 0;

    int V;
    while (1) {
        // 查找未收录节点中距离的最小值
        V = -1;
        for (int i = 0; i < G->Nv; i++) {
            if (!collected[i] && (V == -1 || dist[i] < dist[V]))
                V = i;
        }
        // 未找到则退出
        if (V == -1) break;
        // 将V收录进来
        collected[V] = 1;
        // 检查V的每个邻接点的距离值是否需要更新
        for (AdjaList L = G->edges[V]; L; L = L->next) {
            // 只访问未收录节点
            if (!collected[L->V]) {
                // 距离更小，则更新距离和价格
                if (dist[V] + L->len < dist[L->V]) {
                    dist[L->V] = dist[V] + L->len;
                    price[L->V] = price[V] + L->price;
                } else if (dist[V] + L->len == dist[L->V] && price[V] + L->price < price[L->V]) {
                    // 距离相等但是更加便宜，则只更新价格
                    price[L->V] = price[V] + L->price;
                }
            }
        }
    }

    // 输出结果
    printf("%d %d\n", dist[D], price[D]);

    free(price);
    free(dist);
    free(collected);
}