// 08-图9 关键活动
#include <stdio.h>
#include <stdlib.h>

/**************************  图类型定义开始  ********************************/
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
    AdjaList *InEdges, *OutEdges;
    int *InDegree, *OutDegree;
};
typedef struct LGraphStruct *LGraph;
#define INFINITY 10000000

// 声明图类型函数
LGraph CreateGraph(int Nv);
void FreeGraph(LGraph G);
void AddEdge(LGraph G, Vertex V1, Vertex V2, int len);
/**************************  图类型定义结束  ********************************/


/**************************  队列类型定义开始  ********************************/
// 队列类型定义
typedef int QueueElemType;
struct QueueStruct {
    QueueElemType *elements;
    int front, rear;
    int capacity, nums;
};
typedef struct QueueStruct *Queue;

// 队列函数声明
Queue CreatQueue(int capacity);
void FreeQueue(Queue Q);
int AddQueue(Queue Q, QueueElemType X);
int DeleteQueue(Queue Q, QueueElemType *X);
int QueueLength(Queue Q);
/**************************  队列类型定义结束  ********************************/


// 声明图拓扑排序函数
void TopSort(LGraph G);

// 主函数
int main() {
    int N, M;
    int S, E, L;

    // 初始化并读入图
    scanf("%d %d", &N, &M);
    LGraph G = CreateGraph(N);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &S, &E, &L);
        AddEdge(G, S - 1, E - 1, L);
    }

    // 拓扑排序
    TopSort(G);

    FreeGraph(G);
    return 0;
}

// 拓扑排序
void TopSort(LGraph G) {
    // 定义并初始化earliest和latest数组
    int *earliest = (int *)malloc(sizeof(int) * G->Nv);
    int *latest = (int *)malloc(sizeof(int) * G->Nv);
    for (int i = 0; i < G->Nv; i++) {
        earliest[i] = -1;
        latest[i] = INFINITY;
    }

    // 查找入度为零的节点并入列
    Queue Q = CreatQueue(G->Nv);
    for (int i = 0; i < G->Nv; i++)
        if (G->InDegree[i] == 0) {
            AddQueue(Q, i);
            earliest[i] = 0;
        }
    
    // 计算所有节点的earliest值
    // 当队列非空时，取出一个节点V
    int V, cnt = 0, result = -1;
    while (DeleteQueue(Q, &V) == 0) {
        cnt++;
        // 对V的每个出度边，更新earliest值并删除这条边
        for (AdjaList L = G->OutEdges[V]; L; L = L->next) {
            if (earliest[V] + L->len > earliest[L->V])
                earliest[L->V] = earliest[V] + L->len;
            if (--G->InDegree[L->V] == 0)
                AddQueue(Q, L->V);
        }
        // 若V出度为0，则是结束点，记录结果
        if (G->OutDegree[V] == 0 && earliest[V] > result)
            result = earliest[V];
    }

    // 判断是否可行，不可行则直接结束
    if (cnt != G->Nv) {
        printf("0\n");
        goto end;
    }
    // 打印工程需要的时间
    printf("%d\n", result);

    // 查找出度为零的节点并入列
    for (int i = 0; i < G->Nv; i++)
        if (G->OutDegree[i] == 0) {
            AddQueue(Q, i);
            latest[i] = result;
        }
    
    // 计算所有节点的latest值
    // 当队列非空时，取出一个节点V
    while (DeleteQueue(Q, &V) == 0) {
        // 对V的每个入度边，更新latest值并删除这条边
        for (AdjaList L = G->InEdges[V]; L; L = L->next) {
            if (latest[V] - L->len < latest[L->V])
                latest[L->V] = latest[V] - L->len;
            if (--G->OutDegree[L->V] == 0)
                AddQueue(Q, L->V);
        }
    }

    // 检查每条边是否是关键活动并输出
    for (Vertex V = 0; V < G->Nv; V++) {
        for (AdjaList L = G->OutEdges[V]; L; L = L->next) {
            if (latest[L->V] - earliest[V] == L->len)
                printf("%d->%d\n", V + 1, L->V + 1);
        }
    }

end:
    free(earliest);
    free(latest);
    FreeQueue(Q);
}


/**************************  图类型函数定义开始  ********************************/
// 创建一个指定节点数的空图
LGraph CreateGraph(int Nv) {
    LGraph G = (LGraph)malloc(sizeof(struct LGraphStruct));
    G->Nv = Nv;
    G->Ne = 0;
    G->InDegree = (int *)malloc(sizeof(int) * Nv);
    G->OutDegree = (int *)malloc(sizeof(int) * Nv);
    G->InEdges = (AdjaList *)malloc(sizeof(AdjaList) * Nv);
    G->OutEdges = (AdjaList *)malloc(sizeof(AdjaList) * Nv);
    for (int i = 0; i < G->Nv; i++) {
        G->InDegree[i] = G->OutDegree[i] = 0;
        G->InEdges[i] = G->OutEdges[i] = NULL;
    }
    return G;
}

// 释放图的存储空间
void FreeGraph(LGraph G) {
    // 将每个节点的邻接表空间释放掉
    for (int i = 0; i < G->Nv; i++) {
        AdjaList L = G->InEdges[i], temp;
        while (L) {
            temp = L;
            L = L->next;
            free(temp);
        }
        L = G->OutEdges[i];
        while (L) {
            temp = L;
            L = L->next;
            free(temp);
        }
    }
    // 释放图结构的空间
    free(G->InDegree);
    free(G->OutDegree);
    free(G->InEdges);
    free(G->OutEdges);
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
    // 在V1的出表中添加V2
    G->OutEdges[V1] = MakeAdjaListNode(V2, len, G->OutEdges[V1]);
    // 在V2的入表中添加V1
    G->InEdges[V2] = MakeAdjaListNode(V1, len, G->InEdges[V2]);
    // 增加入度及出度
    G->OutDegree[V1]++;
    G->InDegree[V2]++;
}
/**************************  图类型函数定义结束  ********************************/


/**************************  队列函数定义开始  ********************************/
// 创建一个容量为N的队列
Queue CreatQueue(int capacity) {
    Queue Q = (Queue)malloc(sizeof(struct QueueStruct));
    Q->elements = (QueueElemType *)malloc(sizeof(QueueElemType) * capacity);
    Q->front = Q->rear = capacity - 1;
    Q->capacity = capacity;
    Q->nums = 0;
    return Q;
}

// 释放队列存储空间
void FreeQueue(Queue Q) {
    free(Q->elements);
    free(Q);
}

// 队列q添加一个元素x，返回0成功，返回-1失败
int AddQueue(Queue Q, QueueElemType X) {
    if (Q->nums == Q->capacity) return -1;
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->elements[Q->rear] = X;
    Q->nums++;
    return 0;
}

// 队列q删除一个元素并赋值给*x，返回0成功，返回-1失败
int DeleteQueue(Queue Q, QueueElemType *X) {
    if (Q->nums == 0) return -1;
    Q->front = (Q->front + 1) % Q->capacity;
    *X = Q->elements[Q->front];
    Q->nums--;
    return 0;
}

// 返回队列内元素个数
int QueueLength(Queue Q) {
    return (Q->nums);
}
/**************************  队列函数定义结束  ********************************/