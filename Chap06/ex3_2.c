// 06-图3 六度空间
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

// 队列类型定义
struct BFSVertex {
    Vertex V;
    int level;
};
typedef struct BFSVertex QueueElemType;
struct QueueStruct {
    QueueElemType *elements;
    int first;
    int last;
    int N;
    int nums;
};
typedef struct QueueStruct *Queue;

// 队列函数声明
Queue CreatQueue(int N);
void FreeQueue(Queue q);
int AddQueue(Queue q, QueueElemType x);
int DeleteQueue(Queue q, QueueElemType *x);
int QueueLength(Queue q);

// 声明图的BFS函数
void BFS(LGraph G, Queue q, Vertex V);

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

    // 对每个节点计算占比并输出
    Queue q = CreatQueue(N);
    for (Vertex V = 0; V < N; V++) {
        BFS(G, q, V);
    }

    FreeQueue(q);
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

// 从节点V开始广度优先遍历图，最多6层并记录个数
void BFS(LGraph G, Queue q, Vertex V) {
    int count = 0;
    struct BFSVertex t;

    // 清除访问记录数组
    ClearVisited(G);
    // 访问并记录出发节点
    G->visited[V] = 1;
    count++;
    // 将出发节点加入队列
    t.V = V;
    t.level = 1;
    AddQueue(q, t);
    // 当队列非空时
    while (DeleteQueue(q, &t) == 0) {
        // 对队列取出的节点依次访问其邻接点
        for (AdjaList L = G->edges[t.V]; L; L = L->next) {
            // 若未访问过，则访问并记录
            if (G->visited[L->V]) continue;
            G->visited[L->V] = 1;
            count++;
            // 如果当前访问的节点不满6层，则将该节点加入队列
            if (t.level < 6) {
                struct BFSVertex tv;
                tv.V = L->V;
                tv.level = t.level + 1;
                AddQueue(q, tv);
            }
        }
    }
    // 计算占比并输出
    printf("%d: %.2lf%%\n", V + 1, (double)count / G->Nv * 100);
}

// 创建一个容量为N的队列
Queue CreatQueue(int N) {
    Queue q = (Queue)malloc(sizeof(struct QueueStruct));
    q->elements = (QueueElemType *)malloc(sizeof(QueueElemType) * N);
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
int AddQueue(Queue q, QueueElemType x) {
    if (q->nums == q->N) return -1;
    q->last = (q->last + 1) % q->N;
    q->elements[q->last] = x;
    q->nums++;
    return 0;
}

// 队列q删除一个元素并赋值给*x，返回0成功，返回-1失败
int DeleteQueue(Queue q, QueueElemType *x) {
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