// 08-图8 How Long Does It Take
#include <stdio.h>
#include <stdlib.h>

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

// 定义图类型
int G[100][100];
int N, M;
int Indegree[100];
int earliest[100];

// 声明图函数
void TopSort();

// 主函数
int main() {
    int S, E;

    // 初始化并读入图
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            G[i][j] = -1;
        Indegree[i] = 0;
        earliest[i] = -1;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &S, &E);
        scanf("%d", &G[S][E]);
        Indegree[E]++;
    }

    // 拓扑排序
    TopSort();

    return 0;
}

// 拓扑排序
void TopSort() {
    // 查找入度为零的节点并入列
    Queue Q = CreatQueue(N);
    for (int i = 0; i < N; i++)
        if (Indegree[i] == 0) {
            AddQueue(Q, i);
            earliest[i] = 0;
        }
    
    // 当队列非空时，取出一个节点V
    int V, cnt = 0, flag, result = -1;
    while (DeleteQueue(Q, &V) == 0) {
        cnt++;
        // 对V的每个出度边，更新earliest值并删除这条边
        flag = 0;
        for (int i = 0; i < N; i++) {
            if (G[V][i] != -1) {
                flag = 1;
                if (earliest[V] + G[V][i] > earliest[i])
                    earliest[i] = earliest[V] + G[V][i];
                if (--Indegree[i] == 0)
                    AddQueue(Q, i);
            }
        }
        // 若V出度为0，则是结束点，记录结果
        if (!flag && earliest[V] > result)
            result = earliest[V];
    }

    // 判断是否成功并输出结果
    if (cnt == N) printf("%d\n", result);
    else printf("Impossible\n");

    FreeQueue(Q);
}

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