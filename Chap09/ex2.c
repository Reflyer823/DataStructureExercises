// 09-排序2 Insert or Merge
#include <stdio.h>

int N, init[100], part[100];

// 声明函数
int isInsertion();
void Insertion(int cur);
void MergeSort();

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
        printf("Merge Sort\n");
        MergeSort();
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

// 将start1到end1和start2到end2的两个序列归并后放回原位
void Merge(int start1, int start2, int end2) {
    int temp[100], end1 = start2 - 1;
    int p1 = start1, p2 = start2, p = start1;
    while (p1 <= end1 && p2 <= end2) {
        if (part[p1] <= part[p2]) temp[p++] = part[p1++];
        else temp[p++] = part[p2++];
    }
    while (p1 <= end1) temp[p++] = part[p1++];
    while (p2 <= end2) temp[p++] = part[p2++];
    // 将归并后的数据拷贝回原始数组
    for (int i = start1; i < p; i++)
        part[i] = temp[i];
}

// 进行一轮归并排序
void MergeSort() {
    // 查找当前的size，即寻找有序部分长度的最小值，最后一部分尾巴的长度忽略
    int size = N, cur = 1;
    for (int i = 1; i < N; i++) {
        if (part[i] >= part[i - 1]) cur++;
        else {
            if (cur < size) size = cur;
            cur = 1;
        }
    }
    // 再进行一轮归并
    cur = 0;
    while (cur + size * 2 <= N) {
        Merge(cur, cur + size, cur + size * 2 - 1);
        cur += size * 2;
    }
    // 若最后还剩下两块，则再做一次
    if (cur + size < N)
        Merge(cur, cur + size, N - 1);
}