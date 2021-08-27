// KMP 串的模式匹配
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 定义最大长度
#define MAX_STR_LEN 1000000
#define MAX_PAT_LEN 100000

// 声明函数
typedef char *Position;
Position NaiveSolution(char *String, char *Pattern);
Position SumSolution(char *String, char *Pattern);
Position KMP(char *String, char *Pattern);

// 主函数
int main() {
    char String[MAX_STR_LEN + 1];
    char Pattern[MAX_PAT_LEN + 1];
    int N;
    Position p;

    scanf("%s", String);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", Pattern);
        if ((p = KMP(String, Pattern))) {
            printf("%s\n", p);
        } else {
            printf("Not Found\n");
        }
    }

    return 0;
}

// 从头开始比较字符串s1和s2是否相等
int StrCompare(char *s1, char *s2) {
    for (; *s1 && *s2; s1++, s2++) {
        if (*s1 != *s2) return 0;
    }
    // 若s1不短于s2，则返回相等
    return (*s2 == 0);
}

// 朴素解法，String从头到尾依次尝试匹配
Position NaiveSolution(char *String, char *Pattern) {
    for (; *String; String++) {
        if (StrCompare(String, Pattern))
            return String;
    }
    return NULL;
}

// 朴素解法的改进，先验证子串的和是否与Pattern的和相等，相等再尝试匹配
Position SumSolution(char *String, char *Pattern) {
    int slen = strlen(String), plen = strlen(Pattern);
    int psum = 0, sum = 0;
    // 分别对String和Pattern求前plen个字符的和
    for (int i = 0; i < plen; i++) {
        psum += Pattern[i];
        sum += String[i];
    }
    // 若头部匹配就成功，则直接返回
    if (sum == psum && StrCompare(String, Pattern))
        return String;
    // String的窗口依次后移
    for (int i = 1; i <= slen - plen; i++) {
        // 计算新窗口中的总和
        sum = sum - String[i - 1] + String[i + plen - 1];
        // 若和相等，则尝试匹配
        if (sum == psum && StrCompare(String + i, Pattern))
            return (String + i); 
    }
    // 找不到，返回空指针
    return NULL;
}

// 根据Pattern字符串创建match数组
void BuildMatch(char *Pattern, int *match, int Plen) {
    int i;
    match[0] = -1;
    for (int j = 1; j < Plen; j++) {
        match[j] = -1;
        i = j - 1;
        while (i >= 0) {
            i = match[i];
            if (Pattern[i + 1] == Pattern[j]) {
                match[j] = i + 1;
                break;
            }
        }
    }
}

// KMP匹配算法
Position KMP(char *String, char *Pattern) {
    // 计算字符串长度并验证
    int Slen = strlen(String), Plen = strlen(Pattern);
    if (Slen < Plen) return NULL;

    // 分配match数组空间并计算
    int *match = (int *)malloc(sizeof(int) * Plen);
    BuildMatch(Pattern, match, Plen);

    // 开始匹配
    int s = 0, p = 0;
    while (s < Slen && p < Plen) {
        if (String[s] == Pattern[p]) s++, p++;
        else if (p > 0) p = match[p - 1] + 1;
        else s++;
    }
    free(match);

    // 若p到了Pattern末尾，则匹配成功
    return (p == Plen ? (String + (s - Plen)) : NULL);
}