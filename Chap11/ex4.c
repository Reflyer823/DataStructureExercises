// 11-散列4 Hashing - Hard Version
#include <stdio.h>
#include <stdlib.h>

/**************************  堆类型定义开始  ********************************/
// 定义堆数据类型
struct ArrayRecord{
    int value;
    int index;
};
typedef struct ArrayRecord ElementType;

// 定义堆类型
#define HEAP_MIN_VAL (-1)
typedef struct HeapStruct *Heap;
struct HeapStruct {
    ElementType *nodes;
    int size;
    int capacity;
};

// 声明堆类型函数
Heap CreateHeap(int capacity);
void FreeHeap(Heap H);
int GetHeap(Heap H, ElementType *val);
int InsertHeap(Heap H, ElementType val);
/**************************  堆类型定义结束  ********************************/

// 返回指定散列值的插入位置
int GetInsertIndex(int hash, char *inserted, int N) {
    int index = hash;
    // 当该位置上已有元素时
    while (inserted[index]) {
        // 循环后移一位，当回到起点时，表示已满，返回失败
        if ((index = (index + 1) % N) == hash)
            return -1;
    }
    return index;
}

// 主函数
int main() {
    int N;
    ElementType record;

    // 从输入中读取N并分配各个数组空间
    scanf("%d", &N);
    int *table = (int *)malloc(sizeof(int) * N);
    int *hashes = (int *)malloc(sizeof(int) * N);
    char *added = (char *)malloc(sizeof(char) * N);
    char *inserted = (char *)malloc(sizeof(char) * N);
    Heap H = CreateHeap(N);

    for (int i = 0; i < N; i++) {
        // 读取散列表的值
        scanf("%d", &table[i]);
        inserted[i] = 0;
        // 若当前位置为空，则跳过
        if (table[i] < 0) {
            hashes[i] = -1;
            added[i] = 0;
            continue;
        }
        // 计算散列值，若正好是当前下标，则加入堆中
        hashes[i] = table[i] % N;
        if (hashes[i] == i) {
            record.index = i;
            record.value = table[i];
            InsertHeap(H, record);
            added[i] = 1;
        } else added[i] = 0;
    }

    // 当堆中还有元素时，取出堆顶的最小元素
    int flag = 0, index;
    while (GetHeap(H, &record) == 0) {
        // 标记该位置为已插入
        index = record.index;
        inserted[index] = 1;
        // 打印该位置的值
        if (!flag) {
            printf("%d", table[index]);
            flag = 1;
        } else printf(" %d", table[index]);
        // 移动到右边第一个空位处
        index = GetInsertIndex(index, inserted, N);
        // 若该空位是否是可插入状态，则加入堆中
        if (index != -1 && !added[index] && table[index] >= 0 && GetInsertIndex(hashes[index], inserted, N) == index) {
            record.index = index;
            record.value = table[index];
            InsertHeap(H, record);
            added[index] = 1;
        }
    }

    // 释放各个数组的空间
    free(table);
    free(hashes);
    free(added);
    free(inserted);
    FreeHeap(H);
    return 0;
}

/**************************  堆类型函数定义开始  ********************************/
// 创建一个指定容量的堆
Heap CreateHeap(int capacity) {
    Heap H = (Heap)malloc(sizeof(struct HeapStruct));
    H->nodes = (ElementType *)malloc(sizeof(ElementType) * (capacity + 1));
    H->nodes[0].value = HEAP_MIN_VAL;
    H->size = 0;
    H->capacity = capacity;
    return H;
}

// 释放堆的存储空间
void FreeHeap(Heap H) {
    free(H->nodes);
    free(H);
}

// 取出堆顶元素到val中
int GetHeap(Heap H, ElementType *val) {
    int Parent, Son;
    ElementType temp;
    // 当堆为空时，返回错误
    if (H->size == 0) return -1;
    // 将堆顶元素保存到val中
    *val = H->nodes[1];
    // 保存原来最后一个的元素
    temp = H->nodes[H->size--];
    // 从根节点进行下沉调整
    for (Parent = 1; Parent * 2 <= H->size; Parent = Son) {
        Son = Parent * 2;
        if (Son + 1 <= H->size && H->nodes[Son + 1].value < H->nodes[Son].value)
            Son++;
        if (temp.value <= H->nodes[Son].value) break;
        else H->nodes[Parent] = H->nodes[Son];
    }
    H->nodes[Parent] = temp;
    return 0;
}

// 向堆中插入元素val
int InsertHeap(Heap H, ElementType val) {
    // 当堆已满时，返回错误
    if (H->size == H->capacity) return -1;
    int target;
    // 从最后一个位置向上，寻找合适的位置插入
    for (target = ++H->size; H->nodes[target / 2].value > val.value; target /= 2)
        H->nodes[target] = H->nodes[target / 2];
    H->nodes[target] = val;
    return 0;
}
/**************************  堆类型函数定义结束  ********************************/