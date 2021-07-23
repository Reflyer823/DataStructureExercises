// 04-树6 Complete Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

// 定义完全二叉树类型
typedef struct CBTNode *CBT;
struct CBTNode {
    int *nodes;
    int root;
    int N;
};

// 声明完全二叉树类型的函数
void Sort(int *nums, int N);
CBT MakeTree(int N);
void FreeTree(CBT T);
void FillTree(CBT T, int **p);
void PrintTree(CBT T);

// 主函数
int main() {
    int N;
    int *input;

    // 读取输入序列并排序
    scanf("%d", &N);
    input = (int *) malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &input[i]);
    Sort(input, N);

    // 构造完全二叉搜索树并打印
    CBT T = MakeTree(N);
    int *p = input;
    FillTree(T, &p);
    PrintTree(T);

    FreeTree(T);
    free(input);
    return 0;
}

// 序列进行冒泡排序
void Sort(int *nums, int N) {
    int temp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

// 创建一颗N个节点的完全二叉树
CBT MakeTree(int N) {
    CBT T = (CBT) malloc(sizeof(struct CBTNode));
    T->nodes = (int *) malloc(sizeof(int) * N);
    T->root = 1;
    T->N = N;
    return T;
}

// 释放完全二叉树T占用的空间
void FreeTree(CBT T) {
    free(T->nodes);
    free(T);
}

// 使用p指向的数组填充完全二叉搜索树T
void FillTree(CBT T, int **p) {
    int root = T->root;
    // 若左子树存在，先填充左子树
    if (root * 2 <= T->N) {
        T->root = root * 2;
        FillTree(T, p);
    }
    // 填充根节点
    T->nodes[root - 1] = *((*p)++);
    // 若右子树存在，再填充右子树
    if (root * 2 + 1 <= T->N) {
        T->root = root * 2 + 1;
        FillTree(T, p);
    }
    // 恢复树根节点的值
    T->root = root;
}

// 层序打印完全二叉树T
void PrintTree(CBT T) {
    for (int i = 0; i < T->N; i++) {
        if (i != 0) printf(" ");
        printf("%d", T->nodes[i]);
    }
}