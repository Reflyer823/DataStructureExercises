// 05-树9 Huffman Codes
#include <stdio.h>
#include <stdlib.h>

// 定义堆类型
#define HEAP_MIN_VAL (-1)
typedef struct HeapStruct *Heap;
struct HeapStruct {
    int *nodes;
    int size;
    int capacity;
};

// 声明堆类型函数
Heap CreateHeap(int capacity);
void FreeHeap(Heap H);
int ReadHeap(Heap H, int val);
void BuildHeap(Heap H);
int InsertHeap(Heap H, int val);
int DeleteHeap(Heap H, int *val);

// 定义二叉树类型
typedef struct BinTreeNode *BinTree;
struct BinTreeNode {
    int flag;
    BinTree left;
    BinTree right;
};

// 声明二叉树函数
BinTree CreateTreeNode();
void FreeTree(BinTree T);

// 获取字符c对应的数组下标
int GetIndex(char c) {
    if (c >= '0' && c <= '9')
        return (c - '0');
    else if (c >= 'a' && c <= 'z')
        return (c - 'a' + 10);
    else if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 36);
    else
        return (62);
}

// 主函数
int main() {
    int N, M, times, minLen = 0;
    char c;
    int freq[63] = {0};

    // 读取输入字符及频率，初始化并建立堆
    scanf("%d\n", &N);
    Heap H = CreateHeap(N);
    for (int i = 0; i < N; i++) {
        scanf("%c %d ", &c, &times);
        freq[GetIndex(c)] = times;
        ReadHeap(H, times);
    }
    BuildHeap(H);

    // 求最小的编码总长度，保存在minLen中
    // 哈夫曼树的编码长度等于各个叶节点权值与路径长度乘积之和
    // 同时这个值也等于非叶节点之和
    int v1 = 0, v2 = 0;
    while (1) {
        DeleteHeap(H, &v1);
        if (DeleteHeap(H, &v2) == -1)
            break;
        v1 += v2;
        minLen += v1;
        InsertHeap(H, v1);
    }
    FreeHeap(H);

    // 读取各个测试编码
    scanf("%d", &M);
    char str[64];
    int result, codeLen, l;
    BinTree T, TC;
    // 读取第i份测试编码
    for (int i = 0; i < M; i++) {
        result = 1;
        codeLen = 0;
        T = CreateTreeNode();
        // 读取第j个字符的编码
        for (int j = 0; j < N; j++) {
            scanf("\n%c %s", &c, str);
            // printf("%c %s\n", c, str);
            // 当已经判断为错误时，跳过
            if (result) {
                l = 0;
                TC = T;
                while (str[l]) {
                    // 根据编码是0或1分别创建左右节点
                    if (str[l] == '0') {
                        if (!TC->left) TC->left = CreateTreeNode();
                        TC = TC->left;
                    } else {
                        if (!TC->right) TC->right = CreateTreeNode();
                        TC = TC->right;
                    }
                    // 当经过已有节点时，不是前缀码，错误
                    if (TC->flag) {
                        result = 0;
                        break;
                    }
                    l++;
                }
                // 若目标节点不是叶节点或有重复，错误
                if ((TC->left || TC->right) || TC->flag)
                    result = 0;
                TC->flag = 1;
                // 累加编码总长度
                codeLen += l * freq[GetIndex(c)];
            }
        }
        FreeTree(T);
        // 若是前缀码但编码总长度不是最优的，错误
        if (result && codeLen != minLen) result = 0;
        if (result) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}

// 创建一个指定容量的堆
Heap CreateHeap(int capacity) {
    Heap H = (Heap)malloc(sizeof(struct HeapStruct));
    H->nodes = (int *)malloc(sizeof(int) * (capacity + 1));
    H->nodes[0] = HEAP_MIN_VAL;
    H->size = 0;
    H->capacity = capacity;
    return H;
}

// 释放堆的存储空间
void FreeHeap(Heap H) {
    free(H->nodes);
    free(H);
}

// 插入一个堆的初始元素值
int ReadHeap(Heap H, int val) {
    if (H->size == H->capacity) return -1;
    H->nodes[++H->size] = val;
    return 0;
}

// 对以r为根的子树进行堆的下沉调整
void PercDown(Heap H, int r) {
    int Parent, Son, temp;
    temp = H->nodes[r];
    for (Parent = r; Parent * 2 <= H->size; Parent = Son) {
        Son = Parent * 2;
        if (Son + 1 <= H->size && H->nodes[Son + 1] < H->nodes[Son])
            Son++;
        if (temp <= H->nodes[Son]) break;
        else H->nodes[Parent] = H->nodes[Son];
    }
    H->nodes[Parent] = temp;
}

// 从初始值建立最小堆
void BuildHeap(Heap H) {
    for (int i = H->size / 2; i > 0; i--)
        PercDown(H, i);
}

// 向堆中插入元素val
int InsertHeap(Heap H, int val) {
    if (H->size == H->capacity) return -1;
    int target;
    for (target = ++H->size; H->nodes[target / 2] > val; target /= 2)
        H->nodes[target] = H->nodes[target / 2];
    H->nodes[target] = val;
    return 0;
}

// 从堆中取出一个元素
int DeleteHeap(Heap H, int *val) {
    if (H->size == 0) return -1;
    *val = H->nodes[1];
    H->nodes[1] = H->nodes[H->size--];
    PercDown(H, 1);
    return 0;
}

// 创建一个树节点
BinTree CreateTreeNode() {
    BinTree T = (BinTree)malloc(sizeof(struct BinTreeNode));
    T->flag = 0;
    T->left = T->right = NULL;
    return T;
}

// 释放树的存储空间
void FreeTree(BinTree T) {
    if (T->left) FreeTree(T->left);
    if (T->right) FreeTree(T->right);
    free(T);
}