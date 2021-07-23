// 04-树5 Root of AVL Tree
#include <stdio.h>
#include <stdlib.h>

// 定义AVLTree类型
typedef struct AVLTreeNode *AVLTree;
struct AVLTreeNode {
    int val;
    AVLTree left;
    AVLTree right;
    int height;
};

// 声明AVLTree函数
AVLTree CreateNode(int val);
AVLTree InsertTree(AVLTree T, int val);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
int GetTreeHeight(AVLTree T);
void FreeTree(AVLTree T);
int max(int x, int y);

// 主函数
int main() {
    int N;
    int val;
    AVLTree T = NULL;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &val);
        T = InsertTree(T, val);
    }
    printf("%d\n", T->val);

    FreeTree(T);
    return 0;
}

// 释放AVL树T的存储空间
void FreeTree(AVLTree T) {
    if (T->left) FreeTree(T->left);
    if (T->right) FreeTree(T->right);
    free(T);
}

// 创建一个值为val的节点并返回
AVLTree CreateNode(int val) {
    AVLTree T = (AVLTree) malloc(sizeof(struct AVLTreeNode));
    T->val = val;
    T->left = T->right = NULL;
    T->height = 1;
    return T;
}

// 返回x和y中的最大值
int max(int x, int y) {
    return (x > y ? x : y);
}

// 返回AVL树T的高度
int GetTreeHeight(AVLTree T) {
    if (T) return (T->height);
    else return 0;
}

// 向AVL树T中插入值val
AVLTree InsertTree(AVLTree T, int val) {
    // 若T为空树，返回新建的节点
    if (T == NULL) return CreateNode(val);
    if (val < T->val) {
        // 插入值比当前值小，则向左子树插入
        T->left = InsertTree(T->left, val);
        // 插入后若不平衡，则做调整
        if (GetTreeHeight(T->left) - GetTreeHeight(T->right) == 2) {
            if (val < T->left->val) {
                // 左单旋
                T = SingleLeftRotation(T);
            } else {
                // 左-右双旋
                T->left = SingleRightRotation(T->left);
                T = SingleLeftRotation(T);
            }
        }
    } else if (val > T->val) {
        // 插入值比当前值大，则向右子树插入
        T->right = InsertTree(T->right, val);
        // 插入后若不平衡，则做调整
        if (GetTreeHeight(T->left) - GetTreeHeight(T->right) == -2) {
            if (val > T->right->val) {
                // 右单旋
                T = SingleRightRotation(T);
            } else {
                // 右-左双旋
                T->right = SingleLeftRotation(T->right);
                T = SingleRightRotation(T);
            }
        }
    }
    // 否则相等，则什么也不做
    // 更新树高
    T->height = max(GetTreeHeight(T->left), GetTreeHeight(T->right)) + 1;
    return T;
}

// 对AVL树A进行左单旋
AVLTree SingleLeftRotation(AVLTree A) {
    AVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    // 更新AB的树高
    A->height = max(GetTreeHeight(A->left), GetTreeHeight(A->right)) + 1;
    B->height = max(GetTreeHeight(B->left), GetTreeHeight(B->right)) + 1;
    return B;
}

// 对AVL树A进行右单旋
AVLTree SingleRightRotation(AVLTree A) {
    AVLTree B = A->right;
    A->right = B->left;
    B->left = A;
    // 更新AB的树高
    A->height = max(GetTreeHeight(A->left), GetTreeHeight(A->right)) + 1;
    B->height = max(GetTreeHeight(B->left), GetTreeHeight(B->right)) + 1;
    return B;
}