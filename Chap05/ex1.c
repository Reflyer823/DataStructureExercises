// 05-树7 堆中的路径
#include <stdio.h>
#include <stdlib.h>

// 定义堆类型
#define HEAP_MIN_VAL (-10001)
typedef struct HeapStruct *Heap;
struct HeapStruct {
    int *nodes;
    int size;
    int capacity;
};

// 声明堆类型函数
Heap CreateHeap(int capacity);
void FreeHeap(Heap H);
void ReadHeap(Heap H);
void BuildHeap(Heap H);
int InsertHeap(Heap H, int val);
void PrintHeapNode(Heap H, int i);

// 主函数
int main() {
    int N, M, n;
    Heap H;

    scanf("%d %d", &N, &M);
    H = CreateHeap(N);
    // ReadHeap(H);
    // BuildHeap(H);
    for (int i = 0; i < N; i++) {
        scanf("%d", &n);
        InsertHeap(H, n);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &n);
        PrintHeapNode(H, n);
    }

    FreeHeap(H);
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

// 从输入中读取堆的初始元素值
void ReadHeap(Heap H) {
    for (int i = 1; i <= H->capacity; i++) {
        scanf("%d", &H->nodes[i]);
    }
    H->size = H->capacity;
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

// 打印指定节点的路径
void PrintHeapNode(Heap H, int i) {
    int flag = 0;
    while (i > 0) {
        if (flag) printf(" ");
        else flag = 1;
        printf("%d", H->nodes[i]);
        i /= 2;
    }
    printf("\n");
}