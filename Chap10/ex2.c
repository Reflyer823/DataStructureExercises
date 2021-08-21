// 10-排序5 PAT Judge
#include <stdio.h>
#include <stdlib.h>

// 定义题数K的最大值
#define K_MAX 5

// 定义每个用户记录的结构体类型
struct Record {
    char active;        // 是否活跃，当有了一个编译通过的提交后变为活跃
    int total_score;    // 总分
    int s[K_MAX];       // 记录每道题的最高得分
    int perfect;        // 记录满分的题目数
};

// 定义所有用户记录的数组
struct Record *records;

// 声明希尔排序函数
void Shell_Sort(int *table, int N);

// 主函数
int main() {
    int N, K, M;
    int p[K_MAX];
    int uid, pid, score, real_score;

    // 读取用户数、题目数、记录数
    scanf("%d %d %d", &N, &K, &M);
    // 读取每道题的满分
    for (int i = 0; i < K; i++)
        scanf("%d", &p[i]);
    // 创建N个用户记录数组
    records = (struct Record *)malloc(sizeof(struct Record) * N);
    // 初始化数组
    for (int i = 0; i < N; i++) {
        records[i].active = 0;
        records[i].perfect = 0;
        for (int j = 0; j < K; j++)
            records[i].s[j] = -1;
    }
    // 读取每条记录
    int actN = 0;
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &uid, &pid, &score);
        // 将分数转换为实际得分，编译未通过时得分为0
        real_score = (score == -1 ? 0 : score);
        // 若分数比记录的更高，则更新记录
        if (real_score > records[uid - 1].s[pid - 1]) {
            // 若不是编译没通过的提交，且用户目前还是不活跃，则设置为活跃，活跃人数加一
            if (score != -1 && !records[uid - 1].active) {
                records[uid - 1].active = 1;
                actN++;
            }
            // 更新记录
            records[uid - 1].s[pid - 1] = real_score;
            // 当更新后的分数是这道题的满分时，记录满分数加一
            if (score == p[pid - 1])
                records[uid - 1].perfect++;
        }
    }

    // 对每个人计算总分并生成活跃者的表
    int *table = (int *)malloc(sizeof(int) * actN);
    int ti = 0;
    for (int i = 0; i < N; i++) {
        // 不活跃的跳过
        if (!records[i].active) continue;
        // 记录活跃者的用户id
        table[ti++] = i;
        // 累加总分
        records[i].total_score = 0;
        for (int j = 0; j < K; j++)
            if (records[i].s[j] > 0)
                records[i].total_score += records[i].s[j];
    }

    // 对用户记录进行表排序
    Shell_Sort(table, actN);

    // 输出结果
    int rank = 1, lastTotal = records[table[0]].total_score;
    for (int i = 0; i < actN; i++) {
        // 当总分和上一名不一样时，刷新排名和上一名分数
        if (records[table[i]].total_score != lastTotal) {
            rank = i + 1;
            lastTotal = records[table[i]].total_score;
        }
        // 打印排名、用户id和总分
        printf("%d %05d %d", rank, table[i] + 1, records[table[i]].total_score);
        // 打印每道题成绩
        for (int j = 0; j < K; j++) {
            if (records[table[i]].s[j] >= 0)
                printf(" %d", records[table[i]].s[j]);
            else
                printf(" -");
        }
        // 换行
        printf("\n");
    }

    free(records);
    free(table);
    return 0;
}

// 返回两个记录的比较
int CompareRecord(int i1, int i2) {
    // 当总分不一样时，优先比较总分
    if (records[i1].total_score != records[i2].total_score)
        return (records[i2].total_score - records[i1].total_score);
    // 当总分相等时，若满分题数不同，则比较满分题数
    else if (records[i1].perfect != records[i2].perfect)
        return (records[i2].perfect - records[i1].perfect);
    // 都相等时，比价id的大小 
    else
        return (i1 - i2);
}

// Sedgewick增量的希尔排序
void Shell_Sort(int *table, int N) {
    // Sedgewick增量序列的前28项
    const unsigned int Sedgewick[] = {1, 5, 19, 41, 109, 209, 505, 929,
        2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609, 587521,
        1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 67084289,
        150958081, 268386305, 603906049, 1073643521};
    // 找到不大于N的最大项
    int Si;
    for (Si = 0; Sedgewick[Si] <= N; Si++);
    Si--;
    // 分别取增量数组的第Si到0项作为间隔D
    int D, temp, j;
    for (; Si >= 0; Si--) {
        D = Sedgewick[Si];
        // 进行D间隔的插入排序
        for (int i = D; i < N; i++) {
            temp = table[i];
            for (j = i; j >= D && CompareRecord(table[j - D], temp) > 0; j -= D)
                table[j] = table[j - D];
            table[j] = temp;
        }
    }
}