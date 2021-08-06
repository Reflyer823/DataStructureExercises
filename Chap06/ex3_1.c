// 06-图3 六度空间
/*
 * 本程序是用DFS实现的，但是正常的DFS搜索6层得到的结果是错误的。
 * 例如从节点A出发，在前面搜索到第4层时访问了节点B，因此节点B只向下搜索了2层。
 * 而当后面又在第2层访问到节点B时，因为节点B已被标记访问过，就没有再访问了。
 * 但实际上节点B应向下访问4层而不是2层。因此正常DFS得到的结果会比正确值少。
 * 本程序修改为，不管是否访问过都进行访问，只在计数值增加时判断是否增加过。
 * 但是这样会将图中的很多节点重复访问许多次。当N和M取最大时会超时。
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 定义邻接表类型
typedef int Vertex;
typedef struct AdjaListStruct *AdjaList;
struct AdjaListStruct {
    Vertex V;
    AdjaList next;
};

// 定义图类型
struct LGraphStruct {
    int Nv, Ne;
    AdjaList *edges;
    char *visited;
};
typedef struct LGraphStruct *LGraph;

// 声明图类型函数
LGraph CreateGraph(int Nv);
void FreeGraph(LGraph G);
void AddEdge(LGraph G, Vertex V1, Vertex V2);
void ClearVisited(LGraph G);
void DFS(LGraph G, Vertex V, int level);

// 定义全局变量
int count;

// 主函数
int main() {
    int N, M;
    int V1, V2;
    LGraph G;

    // 从输入中读取图的节点和边
    scanf("%d %d", &N, &M);
    G = CreateGraph(N);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &V1, &V2);
        AddEdge(G, V1 - 1, V2 - 1);
    }

    // 对每个节点计算占比
    for (Vertex V = 0; V < N; V++) {
        count = 0;
        ClearVisited(G);
        DFS(G, V, 0);
        printf("%d: %.2lf%%\n", V + 1, (double)count / N * 100);
    }

    FreeGraph(G);
    return 0;
}

// 创建一个指定节点数的空图
LGraph CreateGraph(int Nv) {
    LGraph G = (LGraph)malloc(sizeof(struct LGraphStruct));
    G->Nv = Nv;
    G->Ne = 0;
    G->visited = (char *)malloc(sizeof(char) * Nv);
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
    free(G->visited);
    free(G->edges);
    free(G);
}

// 在节点V1和V2之间添加一条边
void AddEdge(LGraph G, Vertex V1, Vertex V2) {
    // 边数加一
    G->Ne++;
    // 在V1的邻接表中添加V2
    AdjaList new = (AdjaList)malloc(sizeof(struct AdjaListStruct));
    new->V = V2;
    new->next = G->edges[V1];
    G->edges[V1] = new;
    // 在V2的邻接表中添加V1
    new = (AdjaList)malloc(sizeof(struct AdjaListStruct));
    new->V = V1;
    new->next = G->edges[V2];
    G->edges[V2] = new;
}

// 清除节点访问记录的数组
void ClearVisited(LGraph G) {
    memset(G->visited, 0, sizeof(char) * G->Nv);
}

// 从节点V开始DFS图G，level记录搜索层数
void DFS(LGraph G, Vertex V, int level) {
    if (!G->visited[V]) {
        G->visited[V] = 1;
        count++;
    }
    // 当搜索到第6层时，不再继续向下搜索
    if (level == 6) return;
    // 遍历节点V的邻接表，依次DFS每个未访问过的邻接点
    for (AdjaList L = G->edges[V]; L; L = L->next)
        // if (!G->visited[L->V]) DFS(G, L->V, level + 1);
        DFS(G, L->V, level + 1);
}