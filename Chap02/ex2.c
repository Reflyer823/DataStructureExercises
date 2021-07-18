// 02-线性结构2 一元多项式的乘法与加法运算
#include <stdio.h>
#include <stdlib.h>

// 多项式节点及指针的类型定义
struct PNode {
    int coef;
    int expo;
    struct PNode *next;
};
typedef struct PNode *Polynomial;

Polynomial AppendNode(Polynomial pv, int coef, int expo, Polynomial *p);
Polynomial ReadPoly();
void PrintPoly(Polynomial p);
void FreePoly(Polynomial p);
Polynomial SingleProdPoly(Polynomial p1, Polynomial p2);
Polynomial ProdPoly(Polynomial p1, Polynomial p2);
Polynomial SumPoly(Polynomial p1, Polynomial p2);

int main() {
    /* 测试代码
    Polynomial p1, p2;
    p1 = ReadPoly();
    p2 = ReadPoly();
    PrintPoly(p1);
    PrintPoly(p2);
    FreePoly(p1);
    FreePoly(p2);
    */

    Polynomial p1, p2;
    p1 = ReadPoly();
    p2 = ReadPoly();

    Polynomial p3, p4;
    p3 = ProdPoly(p1, p2);
    p4 = SumPoly(p1, p2);

    PrintPoly(p3);
    PrintPoly(p4);

    FreePoly(p1);
    FreePoly(p2);
    FreePoly(p3);
    FreePoly(p4);
    return 0;
}

// 在给定末尾项pv之后增加一个新节点，当创建新多项式时将头赋值给*p
Polynomial AppendNode(Polynomial pv, int coef, int expo, Polynomial *p) {
    Polynomial node = (Polynomial)malloc(sizeof(struct PNode));
    node->coef = coef;
    node->expo = expo;
    node->next = NULL;
    if (pv) pv->next = node;
    else *p = node;
    return node;
}

// 从输入中读取一个多项式
Polynomial ReadPoly() {
    int N;
    Polynomial p = NULL;
    Polynomial pv = NULL;
    int c, e;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &c, &e);
        pv = AppendNode(pv, c, e, &p);
    }
    return p;
}

// 打印多项式p
void PrintPoly(Polynomial p) {
    char flag = 1;

    if (p == NULL) {
        printf("0 0\n");
        return;
    }

    while (p) {
        if (flag) {
            printf("%d %d", p->coef, p->expo);
            flag = 0;
        } else {
            printf(" %d %d", p->coef, p->expo);
        }
        p = p->next;
    }
    printf("\n");
}

// 释放多项式p占用的内存空间
void FreePoly(Polynomial p) {
    Polynomial temp;
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

// p1单项乘以p2所有项
Polynomial SingleProdPoly(Polynomial p1, Polynomial p2) {
    Polynomial p = NULL, pv = NULL;
    while (p2) {
        pv = AppendNode(pv, p1->coef * p2->coef, p1->expo + p2->expo, &p);
        p2 = p2->next;
    }
    return p;
}

// 返回p1和p2的乘积多项式
Polynomial ProdPoly(Polynomial p1, Polynomial p2) {
    Polynomial p = NULL;

    // 若其中有一个是零多项式，则乘积为零多项式
    if (p1 == NULL || p2 == NULL) return NULL;

    while (p1) {
        if (p == NULL) {
            p = SingleProdPoly(p1, p2);
        } else {
            Polynomial temp1 = SingleProdPoly(p1, p2);
            Polynomial temp2 = p;
            p = SumPoly(temp1, temp2);
            FreePoly(temp1);
            FreePoly(temp2);
        }
        p1 = p1->next;
    }

    return p;
}

// 返回p1和p2的和多项式
Polynomial SumPoly(Polynomial p1, Polynomial p2) {
    Polynomial p = NULL;
    Polynomial pv = NULL;

    while (p1 && p2) {
        if (p1->expo > p2->expo) {
            pv = AppendNode(pv, p1->coef, p1->expo, &p);
            p1 = p1->next;
        } else if (p1->expo < p2->expo) {
            pv = AppendNode(pv, p2->coef, p2->expo, &p);
            p2 = p2->next;
        } else {
            int sum = p1->coef + p2->coef;
            if (sum) {
                pv = AppendNode(pv, sum, p1->expo, &p);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1) {
        pv = AppendNode(pv, p1->coef, p1->expo, &p);
        p1 = p1->next;
    }
    while (p2) {
        pv = AppendNode(pv, p2->coef, p2->expo, &p);
        p2 = p2->next;
    }

    return p;
}