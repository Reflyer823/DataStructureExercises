// 09-排序3 Insertion or Heap Sort
#include <stdio.h>

int N, init[100], part[100];

// 声明函数
int isInsertion();
void Insertion(int cur);
void HeapSort();

// 主函数
int main() {
    // 读取输入数据
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &init[i]);
    for (int i = 0; i < N; i++) scanf("%d", &part[i]);

    // 判断排序类型并作对应处理
    int cur;
    if ((cur = isInsertion())) {
        printf("Insertion Sort\n");
        Insertion(cur);
    } else {
        printf("Heap Sort\n");
        HeapSort();
    }

    // 输出一轮后的数据
    printf("%d", part[0]);
    for (int i = 1; i < N; i++)
        printf(" %d", part[i]);

    return 0;
}

// 判断是否是插入排序，否返回0，是返回当前排到第几个数
int isInsertion() {
    int i;
    // 查找有序部分的结尾
    for (i = 1; i < N && part[i] >= part[i - 1]; i++);
    // 验证后续部分是否和原始序列相同，如有不同则不是插入排序
    for (int j = i; j < N; j++) {
        if (part[j] != init[j]) return 0;
    }
    return i;
}

// 进行一轮插入排序
void Insertion(int cur) {
    int temp = part[cur], i;
    for (i = cur; i > 0 && part[i - 1] > temp; i--)
        part[i] = part[i - 1];
    part[i] = temp;
}

// 进行一轮堆排序
void HeapSort() {
    // 查找下一个目标位置
    int target;
    for (target = 1; target < N; target++) {
        // 若其值比堆中父节点的值大，则找到
        if (part[target] > part[(target - 1) / 2]) {
            target--;
            break;
        }
    }
    // 记录目标位置的值并放置根节点的值
    int X = part[target];
    part[target] = part[0];
    // 对堆进行调整
    int Parent, Child;
    for (Parent = 0; Parent * 2 + 1 < target; Parent = Child) {
        Child = Parent * 2 + 1;
        // 将Child指向值较大的子节点
        if (Child + 1 < target && part[Child + 1] > part[Child])
            Child++;
        if (X >= part[Child])
            break;
        else
            part[Parent] = part[Child];
    }
    part[Parent] = X;
}