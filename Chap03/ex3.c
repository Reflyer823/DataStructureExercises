// 03-树3 Tree Traversals Again
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义树节点类型
struct TreeNode {
    int value;
    char times;
};

// 定义堆栈类型
#define StackElementType struct TreeNode
struct StackNode {
    StackElementType *elements;
    int last;
    int M;
};
typedef struct StackNode *Stack;

// 声明堆栈函数
Stack CreatStack(int M);
int PushStack(Stack s, StackElementType x);
int PopStack(Stack s, StackElementType *x);
void ClearStack(Stack s);
void FreeStack(Stack s);

int main() {
    int N;
    char str[10];
    struct TreeNode node;
    int printFlag = 0;

    scanf("%d\n", &N);
    Stack s = CreatStack(N);
    for (int i = 0; i < 2 * N; i++) {
        scanf("%s", str);
        if (strcmp(str, "Push") == 0) {
            // 当输入Push时，将该节点第一次入栈
            scanf("%d", &node.value);
            node.times = 0;
            PushStack(s, node);
        } else if (strcmp(str, "Pop") == 0) {
            // 将栈顶所有第二次入栈的节点弹出并打印
            do {
                PopStack(s, &node);
                if (node.times == 1) {
                    if (printFlag) printf(" ");
                    else printFlag = 1;
                    printf("%d", node.value);
                }
            } while (node.times == 1);
            // 将弹出的第一次入栈节点重新二次入栈
            node.times = 1;
            PushStack(s, node);
        }
    }
    // 将堆栈中剩余的所有二次入栈节点全部弹出并打印
    while (PopStack(s, &node) == 0) {
        if (printFlag) printf(" ");
        else printFlag = 1;
        printf("%d", node.value);
    }

    FreeStack(s);
    return 0;
}

// 创建一个容量为M的堆栈
Stack CreatStack(int M) {
    Stack s = (Stack)malloc(sizeof(struct StackNode));
    s->last = -1;
    s->M = M;
    s->elements = (StackElementType *)malloc(sizeof(StackElementType) * M);
    return s;
}

// 释放堆栈空间
void FreeStack(Stack s) {
    free(s->elements);
    free(s);
}

// 将x入栈，返回0表示成功，返回-1表示失败
int PushStack(Stack s, StackElementType x) {
    if (s->last == s->M - 1) return -1;
    s->elements[++s->last] = x;
    return 0;
}

// 出栈并赋值给*x，返回0表示成功，返回-1表示失败
int PopStack(Stack s, StackElementType *x) {
    if (s->last == -1) return -1;
    *x = s->elements[s->last--];
    return 0;
}

// 清空堆栈元素
void ClearStack(Stack s) {
    s->last = -1;
}