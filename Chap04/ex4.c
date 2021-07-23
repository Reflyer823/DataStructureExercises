// 04-树7 二叉搜索树的操作集
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

/* 你的代码将被嵌在这里 */
BinTree Insert( BinTree BST, ElementType X ) {
    if (!BST) {
        BST = (BinTree) malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
        return BST;
    }
    if (X > BST->Data) BST->Right = Insert(BST->Right, X);
    else if (X < BST->Data) BST->Left = Insert(BST->Left, X);
    return BST;
}

BinTree Delete( BinTree BST, ElementType X ) {
    if (!BST) {
        printf("Not Found\n");
        return BST;
    }
    if (X > BST->Data) {
        // X比当前值大，去右子树删除
        BST->Right = Delete(BST->Right, X);
    } else if (X < BST->Data) {
        // X比当前值小，去左子树删除
        BST->Left = Delete(BST->Left, X);
    } else {
        // 当前值等于X，删除根节点
        if (BST->Left && BST->Right) {
            // 左右子树都非空，用右子树的最小值代替当前节点
            BinTree RightMin = FindMin(BST->Right);
            BST->Data = RightMin->Data;
            BST->Right = Delete(BST->Right, RightMin->Data);
        } else if (!BST->Left && !BST->Right) {
            // 左右子树都为空，直接删除
            free(BST);
            BST = NULL;
        } else {
            // 只有一个非空子树
            BinTree Son;
            if (BST->Left) Son = BST->Left;
            else Son = BST->Right;
            free(BST);
            BST = Son;
        }
    }
    return BST;
}

Position Find( BinTree BST, ElementType X ) {
    if (!BST) return NULL;
    if (X > BST->Data) return Find(BST->Right, X);
    else if (X < BST->Data) return Find(BST->Left, X);
    else return BST;
}

Position FindMin( BinTree BST ) {
    if (!BST) return NULL;
    while (BST->Left) BST = BST->Left;
    return BST;
}

Position FindMax( BinTree BST ) {
    if (!BST) return NULL;
    while (BST->Right) BST = BST->Right;
    return BST;
}