// 04-树4 是否同一棵二叉搜索树
#include <stdio.h>

// 定义树类型
struct TreeNode {
    int left;
    int right;
    int flag;
};
#define MAX_TREE_NODES 11
struct Tree {
    struct TreeNode nodes[MAX_TREE_NODES];
    int root;
};

// 声明树函数
void ClearTree(struct Tree *t);
void ReadTree(struct Tree *t, int N);
void ResetTree(struct Tree *t);
int Judge(struct Tree *t, int N);

int main() {
    int N, L;
    struct Tree t;

    while (1) {
        scanf("%d", &N);
        if (N == 0) return 0;
        scanf("%d", &L);
        ReadTree(&t, N);
        for (int i = 0; i < L; i++) {
            if (Judge(&t, N)) printf("Yes\n");
            else printf("No\n");
        }
    }
}

// 清空一棵树
void ClearTree(struct Tree *t) {
    t->root = 0;
    for (int i = 1; i < MAX_TREE_NODES; i++) {
        t->nodes[i].left = 0;
        t->nodes[i].right = 0;
        t->nodes[i].flag = 0;
    }
}

// 从输入中读取N个整数，并加入树t中
void ReadTree(struct Tree *t, int N) {
    int v, current;
    ClearTree(t);
    for (int i = 0; i < N; i++) {
        scanf("%d", &v);
        // 若是空树，则将其作为根节点
        if (t->root == 0) t->root = v;
        else {
            // 当前节点指针初始化为根节点
            current = t->root;
            while (1) {
                if (v > current) {
                    // 向右子树移动，若右子树为空则加入该节点
                    if (t->nodes[current].right) current = t->nodes[current].right;
                    else {
                        t->nodes[current].right = v;
                        break;
                    }
                } else if (v < current) {
                    // 向左子树移动，若左子树为空则加入该节点
                    if (t->nodes[current].left) current = t->nodes[current].left;
                    else {
                        t->nodes[current].left = v;
                        break;
                    }
                }
            }
        }
    }
}

// 重置树中所有节点的flag值为0
void ResetTree(struct Tree *t) {
    for (int i = 1; i < MAX_TREE_NODES; i++)
        t->nodes[i].flag = 0;
}

// 判断输入的N个整数的序列是否和树t一致
int Judge(struct Tree *t, int N) {
    int input[MAX_TREE_NODES - 1];
    int current;

    // 读取N个整数输入到数组中
    for (int i = 0; i < N; i++) {
        scanf("%d", &input[i]);
    }
    ResetTree(t);
    for (int i = 0; i < N; i++) {
        current = t->root;
        // 根据当前值与current的大小,选择向左子树或右子树移动
        while (1) {
            if (input[i] > current) {
                // 移动中遇到flag为0的节点直接返回0,表示不一致
                if (t->nodes[current].flag == 0) return 0;
                current = t->nodes[current].right;
            } else if (input[i] < current) {
                if (t->nodes[current].flag == 0) return 0;
                current = t->nodes[current].left;
            } else {
                // 当遇到值相等的节点时将其flag置为1
                t->nodes[current].flag = 1;
                break;
            }
        }
    }
    // 所有输入数值都一致,返回1,表示一致
    return 1;
}