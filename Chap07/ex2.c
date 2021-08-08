// 07-图5 Saving James Bond - Hard Version
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// 队列类型定义
typedef int QueueElemType;
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

// 定义坐标结构体类型和平方宏
struct Location {
    int x, y;
};
#define Square(X) ((X) * (X))

// 主函数
int main() {
    // 从输入中读取各个点的坐标
    int N, D;
    scanf("%d %d", &N, &D);
    struct Location *nodes = (struct Location *)malloc(sizeof(struct Location) * N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &nodes[i].x, &nodes[i].y);
    }

    // 检查是否可以直接跳上岸
    if (7.5 + D >= 50) {
        // 输出一步，退出程序
        printf("1\n");
        free(nodes);
        return 0;
    }

    // 初始化距离数组为0
    char *dist = (char *)malloc(sizeof(char) * N);
    memset(dist, 0, sizeof(char) * N);
    // 初始化上一跳数组为-1
    char *last = (char *)malloc(sizeof(char) * N);
    for (int i = 0; i < N; i++)
        last[i] = -1;
    // 初始化第一跳数组为-1
    int *first = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        first[i] = -1;

    // 无权图的单源最短路算法（BFS）
    Queue Q = CreatQueue(N);
    int V, lastV = -1, firstLen;
    for (int i = 0; i < N; i++) {
        // 若从中心出发可以跳到第i个点上
        if (Square(nodes[i].x) + Square(nodes[i].y) <= Square(7.5 + D)) {
            // 距离设置为1，第一跳设置为自身
            dist[i] = 1;
            first[i] = i;
            // 若从该点就可以直接跳上岸
            if (nodes[i].x >= 50 - D || nodes[i].x <= D - 50 || nodes[i].y >= 50 - D || nodes[i].y <= D - 50) {
                // 如果还没有结果或该结果第一跳更短，则更新结果
                if (lastV == -1 || (Square(nodes[i].x) + Square(nodes[i].y) < firstLen)) {
                    lastV = i;
                    firstLen = Square(nodes[i].x) + Square(nodes[i].y);
                }
            }
            // 将该节点加入队列
            AddQueue(Q, i);
        }
    }
    // 当队列内还有顶点时
    while (DeleteQueue(Q, &V) == 0) {
        // 如果已经有结果并且该节点的邻接点距离已经比结果要大，则退出循环
        if (lastV != -1 && dist[V] + 1 > dist[lastV])
            break;
        // 对每个节点检查是不是未访问过的邻接点
        for (int i = 0; i < N; i++) {
            if (dist[i] == 0 && (Square(nodes[V].x - nodes[i].x) + Square(nodes[V].y - nodes[i].y) <= Square(D))) {
                // 距离为上一步加一，同时记录上一步的节点和第一跳节点
                dist[i] = dist[V] + 1;
                last[i] = V;
                first[i] = first[V];
                // 若当前节点已经可以跳上岸了
                if (nodes[i].x >= 50 - D || nodes[i].x <= D - 50 || nodes[i].y >= 50 - D || nodes[i].y <= D - 50) {
                    // 如果还没有结果或该结果第一跳更短，则更新结果
                    if (lastV == -1 || (Square(nodes[first[i]].x) + Square(nodes[first[i]].y) < firstLen)) {
                        lastV = i;
                        firstLen = Square(nodes[first[i]].x) + Square(nodes[first[i]].y);
                    }
                }
                // 将该节点加入队列
                AddQueue(Q, i);
            }
        }
    }

    // 输出结果
    if (lastV == -1) printf("0\n");
    else {
        // 创建记录路径的数组
        int *path = (int *)malloc(sizeof(int) * dist[lastV]);
        // 打印总跳数为最后一个节点的距离加一
        printf("%d\n", dist[lastV] + 1);
        // 从最后一个节点开始向前寻找路径
        V = lastV;
        for (int i = 0; i < dist[lastV]; i++) {
            path[i] = V;
            V = last[V];
        }
        // 打印出路径上每个点的坐标
        for (int i = dist[lastV] - 1; i >= 0; i--) {
            printf("%d %d\n", nodes[path[i]].x, nodes[path[i]].y);
        }
        free(path);
    }

    FreeQueue(Q);
    free(dist);
    free(last);
    free(first);
    free(nodes);
    return 0;
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