// 10-排序4 统计工龄
#include <stdio.h>

int main() {
    int N, age, count[51] = {0};

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &age);
        count[age]++;
    }
    for (int i = 0; i < 51; i++) {
        if (count[i]) printf("%d:%d\n", i, count[i]);
    }

    return 0;
}