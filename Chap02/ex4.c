// 02-线性结构4 Pop Sequence
#include <stdio.h>
#include <stdlib.h>

// 定义堆栈类型
struct StackNode {
    int *elements;
    int last;
    int M;
};
typedef struct StackNode *Stack;

Stack CreatStack(int M);
int PushStack(Stack s, int x);
int PopStack(Stack s, int *x);
void ClearStack(Stack s);
void FreeStack(Stack s);

int main() {
    int M, N, K;
    scanf("%d %d %d\n", &M, &N, &K);

    int *nums = (int *)malloc(sizeof(int) * N);
    Stack s = CreatStack(M);
    // 对每个输入序列进行判断
    for (int i = 0; i < K; i++) {
        // 读取输入序列到数组nums中
        for (int j = 0; j < N; j++) {
            scanf("%d", &nums[j]);
        }
        ClearStack(s);
        int current = 1, result = 1, popNum;
        for (int j = 0; j < N; j++) {
            // 将当前数之前的所有数都压入堆栈
            while (current <= nums[j]) {
                // 堆栈已满，序列不存在
                if (PushStack(s, current++) == -1) {
                    result = 0;
                    goto printResult;
                }
            }
            // 从栈顶弹出一个元素,若弹出失败或弹出数值不相等,序列不存在
            if (PopStack(s, &popNum) == -1 || popNum != nums[j]) {
                result = 0;
                break;
            }
        }
    printResult:
        if (result) printf("YES\n");
        else printf("NO\n");
    }

    FreeStack(s);
    free(nums);
    return 0;
}

// 创建一个容量为M的堆栈
Stack CreatStack(int M) {
    Stack s = (Stack)malloc(sizeof(struct StackNode));
    s->last = -1;
    s->M = M;
    s->elements = (int *)malloc(sizeof(int) * M);
    return s;
}

// 释放堆栈空间
void FreeStack(Stack s) {
    free(s->elements);
    free(s);
}

// 将x入栈，返回0表示成功，返回-1表示失败
int PushStack(Stack s, int x) {
    if (s->last == s->M - 1) return -1;
    s->elements[++s->last] = x;
    return 0;
}

// 出栈并赋值给*x，返回0表示成功，返回-1表示失败
int PopStack(Stack s, int *x) {
    if (s->last == -1) return -1;
    *x = s->elements[s->last--];
    return 0;
}

// 清空堆栈元素
void ClearStack(Stack s) {
    s->last = -1;
}