// 11-散列1 电话聊天狂人
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 单向链表类型定义
#define KEYSTR_MAX_SIZE 11
typedef char PhoneNumType[KEYSTR_MAX_SIZE + 1];
typedef struct LinkedListNode *LinkedList, *Postion;
struct LinkedListNode {
    PhoneNumType key;
    int count;
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
Postion Find(HashTable H, ElementType key);
void Insert(HashTable H, ElementType key);
void OutputCrazy(HashTable H);

// 主函数
int main() {
    int N;
    PhoneNumType key;
    Postion P;

    // 从输入中读取每个电话号
    scanf("%d", &N);
    HashTable H = CreateTable(N * 2);
    for (int i = 0; i < 2 * N; i++) {
        scanf("%s", key);
        // 若在散列表中能找到，则次数加一
        if ((P = Find(H, key)))
            P->count++;
        // 若找不到，则创建一个新键值
        else
            Insert(H, key);
    }

    // 统计并打印出次数最多的狂人
    OutputCrazy(H);

    DestroyTable(H);
    return 0;
}

// 返回不小于x的下一个素数
#define MAX_TABLE_SIZE 1000000
int NextPrime(int x) {
    int flag;
    for (; x < MAX_TABLE_SIZE; x++) {
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
    // 选取手机号的后五位数，对表长求余得到散列值
    int end5 = atoi(key + KEYSTR_MAX_SIZE - 5);
    return (end5 % TableSize);
}

// 在散列表中查找输入的键值
Postion Find(HashTable H, ElementType key) {
    int hash = HashKey(key, H->TableSize);
    for (Postion P = H->Lists[hash]; P; P = P->next) {
        if (strcmp(P->key, key) == 0) return P;
    }
    return NULL;
}

// 在散列表中插入一个新键值
void Insert(HashTable H, ElementType key) {
    int hash = HashKey(key, H->TableSize);
    Postion new = (Postion)malloc(sizeof(struct LinkedListNode));
    strcpy(new->key, key);
    new->count = 1;
    new->next = H->Lists[hash];
    H->Lists[hash] = new;
}

// 输出散列表中次数最多的电话号及通话次数
void OutputCrazy(HashTable H) {
    PhoneNumType crazyNum;
    int maxCount = 0, crazyCount;
    // 遍历整个散列表中的每个链表
    Postion P;
    for (int i = 0; i < H->TableSize; i++) {
        for (P = H->Lists[i]; P; P = P->next) {
            // 当前手机号通话数大于最大值时，更新最大值
            if (P->count > maxCount) {
                maxCount = P->count;
                strcpy(crazyNum, P->key);
                crazyCount = 1;
            // 当遇到也是最大次数的狂人时，增加狂人数，如果当前的手机号更小，则更新手机号
            } else if (P->count == maxCount) {
                crazyCount++;
                if (strcmp(crazyNum, P->key) > 0)
                    strcpy(crazyNum, P->key);
            }
        }
    }
    // 输出结果
    printf("%s %d", crazyNum, maxCount);
    if (crazyCount > 1) printf(" %d", crazyCount);
}