// 03-树2 List Leaves
#include <stdio.h>
#include <stdlib.h>

// 队列类型定义
struct QueueNode {
    int *elements;
    int first;
    int last;
    int N;
    int nums;
};
typedef struct QueueNode *Queue;

// 队列函数声明
Queue CreatQueue(int N);
void FreeQueue(Queue q);
int AddQueue(Queue q, int x);
int DeleteQueue(Queue q, int *x);
int QueueLength(Queue q);

// 树类型定义
struct TreeNode {
    int left;
    int right;
};
struct Tree {
    struct TreeNode nodes[10];
    int root;
    int N;
};

// 树函数声明
void ReadTree(struct Tree *t);

int main() {
    struct Tree t;
    ReadTree(&t);

    // 层序遍历树，遇到叶子节点时输出
    Queue q = CreatQueue(t.N);
    if (t.root != -1) AddQueue(q, t.root);
    int printFlag = 1;
    while (QueueLength(q) > 0) {
        int node;
        DeleteQueue(q, &node);
        if (t.nodes[node].left != -1) AddQueue(q, t.nodes[node].left);
        if (t.nodes[node].right != -1) AddQueue(q, t.nodes[node].right);
        if (t.nodes[node].left == -1 && t.nodes[node].right == -1) {
            if (printFlag) printFlag = 0;
            else printf(" ");
            printf("%d", node);
        }
    }

    FreeQueue(q);
    return 0;
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

// 从输入中读取一棵树到t中
void ReadTree(struct Tree *t) {
    int N;
    char leftChar, rightChar;
    int check[10] = {0};
    scanf("%d", &N);
    t->N = N;
    for (int i = 0; i < N; i++) {
        // 注意此处字符串前面的换行符，若不加则会将换行符当成字符读入变量中
        scanf("\n%c %c", &leftChar, &rightChar);
        if (leftChar == '-') t->nodes[i].left = -1;
        else {
            t->nodes[i].left = leftChar - '0';
            check[leftChar - '0'] = 1;
        }
        if (rightChar == '-') t->nodes[i].right = -1;
        else {
            t->nodes[i].right = rightChar - '0';
            check[rightChar - '0'] = 1;
        }
    }
    // 查找树根的位置，找不到时为-1（空树）
    t->root = -1;
    for (int i = 0; i < N; i++) {
        if (check[i] == 0) {
            t->root = i;
            break;
        }
    }
}