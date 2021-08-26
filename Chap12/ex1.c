// KMP 串的模式匹配
#include <stdio.h>
#include <string.h>

// 定义最大长度
#define MAX_STR_LEN 1000000
#define MAX_PAT_LEN 100000

// 声明函数
void Naive(char *String, char *Pattern);

// 主函数
int main() {
    char String[MAX_STR_LEN + 1];
    char Pattern[MAX_PAT_LEN + 1];
    int N;

    scanf("%s", String);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", Pattern);
        Naive(String, Pattern);
    }

    return 0;
}

int StrCompare(char *s1, char *s2) {
    for (; *s1 && *s2; s1++, s2++) {
        if (*s1 != *s2) return 0;
    }
    return (*s2 == 0);
}

void Naive(char *String, char *Pattern) {
    for (; *String; String++) {
        if (StrCompare(String, Pattern)) {
            printf("%s\n", String);
            return;
        }
    }
    printf("Not Found\n");
}

void SumSolution(char *String, char *Pattern) {
    int slen = strlen(String), plen = strlen(Pattern);
    int psum = 0, sum = 0;
    for (int i = 0; i < plen; i++) {
        psum += Pattern[i];
        sum += String[i];
    }
    if (sum == psum && StrCompare(String, Pattern)) {
        printf("%s\n", String);
        return;
    } 
    for (int i = 1; i <= slen - plen; i++) {
        sum = sum - String[i - 1] + String[i + plen - 1];
        if (sum == psum && StrCompare(String + i, Pattern)) {
            printf("%s\n", String + i);
            return;
        } 
    }
    printf("Not Found\n");
}