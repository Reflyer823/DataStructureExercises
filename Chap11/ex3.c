// 11-散列3 QQ帐户的申请与登陆
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// QQ号和密码类型定义
#define MAX_QQ_LEN 10
typedef char QQType[MAX_QQ_LEN + 1];
#define MAX_PWD_LEN 16
typedef char PwdType[MAX_PWD_LEN + 1];

// 单向链表类型定义
typedef struct LinkedListNode *LinkedList, *Postion;
struct LinkedListNode {
    QQType qq;
    PwdType pwd;
    Postion next;
};

// 散列表数据类型定义
typedef struct HashTableStruct *HashTable;
struct HashTableStruct {
    int TableSize;
    LinkedList *Lists;
};
typedef char *ElementType;

// 散列表类型函数声明
HashTable CreateTable(int size);
void DestroyTable(HashTable H);
Postion Find(HashTable H, ElementType qq);
void Insert(HashTable H, ElementType qq, ElementType pwd);

// 主函数
int main() {
    int N;
    QQType qq;
    PwdType pwd;
    char cmd;
    Postion P;

    scanf("%d", &N);
    HashTable H = CreateTable(N);
    for (int i = 0; i < N; i++) {
        scanf("\n%c %s %s", &cmd, qq, pwd);
        P = Find(H, qq);
        if (cmd == 'N') {
            if (P) printf("ERROR: Exist\n");
            else {
                Insert(H, qq, pwd);
                printf("New: OK\n");
            }
        } else if (cmd == 'L') {
            if (P) {
                if (strcmp(P->pwd, pwd) == 0) printf("Login: OK\n");
                else printf("ERROR: Wrong PW\n");
            } else printf("ERROR: Not Exist\n");
        }
    }

    DestroyTable(H);
    return 0;
}

// 返回不小于x的下一个素数
#define MAX_TABLE_SIZE 1000000
int NextPrime(int x) {
    int flag;
    for (; x < MAX_TABLE_SIZE; x++) {
        // 注意1不是素数，但是能通过下面的判断算法，遇到1时需要跳过
        if (x == 1) continue;
        flag = 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) break;
    }
    return x;
}

// 创建一个不小于输入大小的散列表
HashTable CreateTable(int size) {
    int TableSize = NextPrime(size);
    HashTable H = (HashTable)malloc(sizeof(struct HashTableStruct));
    H->TableSize = TableSize;
    H->Lists = (LinkedList *)malloc(sizeof(LinkedList) * TableSize);
    // 将每个链表都初始化为空
    for (int i = 0; i < TableSize; i++)
        H->Lists[i] = NULL;
    return H;
}

// 删除并释放散列表的空间
void DestroyTable(HashTable H) {
    Postion L, temp;
    // 释放每个链表的空间
    for (int i = 0; i < H->TableSize; i++) {
        L = H->Lists[i];
        while (L) {
            temp = L;
            L = L->next;
            free(temp);
        }
    }
    free(H->Lists);
    free(H);
}

// 对输入的键值计算散列值
int HashKey(ElementType key, int TableSize) {
    // 使用折叠法，将QQ号每五位数折叠做一次叠加
    int i = 0, sum = 0, cur = 0;
    while (key[i]) {
        cur = cur * 10 + key[i] - '0';
        if (++i % 5 == 0) {
            sum += cur;
            cur = 0;
        }
    }
    sum += cur;
    // 返回折叠总和对表长的余数
    return (sum % TableSize);
}

// 在散列表中查找输入的键值
Postion Find(HashTable H, ElementType key) {
    int hash = HashKey(key, H->TableSize);
    for (Postion P = H->Lists[hash]; P; P = P->next) {
        if (strcmp(P->qq, key) == 0) return P;
    }
    return NULL;
}

// 在散列表中插入一个新键值
void Insert(HashTable H, ElementType qq, ElementType pwd) {
    int hash = HashKey(qq, H->TableSize);
    Postion new = (Postion)malloc(sizeof(struct LinkedListNode));
    strcpy(new->qq, qq);
    strcpy(new->pwd, pwd);
    new->next = H->Lists[hash];
    H->Lists[hash] = new;
}
