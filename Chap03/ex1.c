// 03-树1 树的同构
#include <stdio.h>

struct TreeNode {
    char data;
    int left;
    int right;
};
struct Tree {
    struct TreeNode nodes[10];
    int root;
};

void ReadTree(struct Tree *t);
int IsomorphismTree(struct Tree *t1, int tn1, struct Tree *t2, int tn2);

int main() {
    struct Tree t1, t2;
    ReadTree(&t1);
    ReadTree(&t2);

    if (IsomorphismTree(&t1, t1.root, &t2, t2.root)) printf("Yes\n");
    else printf("No\n");

    return 0;
}

// 从输入中读取一棵树到t中
void ReadTree(struct Tree *t) {
    int N;
    char leftChar, rightChar;
    int check[10] = {0};
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        // 注意此处字符串前面的换行符，若不加则会将换行符当成字符读入变量中
        scanf("\n%c %c %c", &t->nodes[i].data, &leftChar, &rightChar);
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

// 返回输入两颗树是否同构，0表示不同构，1表示同构
int IsomorphismTree(struct Tree *t1, int tn1, struct Tree *t2, int tn2) {
    // 两棵树都为空，同构
    if (tn1 == -1 && tn2 == -1) return 1;
    // 两棵树都为非空
    else if (tn1 != -1 && tn2 != -1) {
        // 根节点数据不等时，不同构
        if (t1->nodes[tn1].data != t2->nodes[tn2].data) return 0;
        // 左右子树对应同构或者左右子树交叉同构时，则同构
        return ((IsomorphismTree(t1, t1->nodes[tn1].left, t2, t2->nodes[tn2].left) && IsomorphismTree(t1, t1->nodes[tn1].right, t2, t2->nodes[tn2].right)) || 
            (IsomorphismTree(t1, t1->nodes[tn1].left, t2, t2->nodes[tn2].right) && IsomorphismTree(t1, t1->nodes[tn1].right, t2, t2->nodes[tn2].left)));
    } else return 0; // 一颗空一颗非空，不同构
}