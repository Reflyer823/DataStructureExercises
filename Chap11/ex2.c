// 11-散列2 Hashing
#include <stdio.h>
#include <stdlib.h>

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

// 主函数
int main() {
    int MSize, N;
    scanf("%d %d", &MSize, &N);

    // 计算表长并分配散列表数组空间
    int TSize = NextPrime(MSize);
    int *HashTable = (int *)malloc(sizeof(int) * TSize);
    for (int i = 0; i < TSize; i++) HashTable[i] = 0;

    // 读取每个插入元素并打印其位置
    int num, key, start, cnum;
    for (int i = 0; i < N; i++) {
        scanf("%d", &num);
        // 初始位置为输入元素的散列值
        start = key = num % TSize;
        cnum = 0;
        // 当散列表中存在冲突时，使用正向平方探测
        while (HashTable[key]) {
            cnum++;
            key = (start + cnum * cnum) % TSize;
            // 当探测回到起点时，退出
            if (key == start) break;
        }
        // 若当前位置在起点，且是有冲突的，那么无法插入
        if (cnum && key == start) printf(" -");
        // 否则将元素插入散列表中，并打印插入位置的下标
        else {
            HashTable[key] = num;
            if (i == 0) printf("%d", key);
            else printf(" %d", key);
        }
    }

    free(HashTable);
    return 0;
}