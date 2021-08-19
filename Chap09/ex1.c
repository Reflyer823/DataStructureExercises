// 09-排序1 排序
#include <stdio.h>
#include <stdlib.h>

// 定义元素类型
typedef int ElementType;

// 函数声明
void Bubble_Sort(ElementType A[], int N);
void Insertion_Sort(ElementType A[], int N);
void Shell_Sort(ElementType A[], int N);
void Selection_Sort(ElementType A[], int N);
void Heap_Sort(ElementType A[], int N);

// 主函数
int main() {
    int N;
    ElementType *A;

    // 读取输入数据
    scanf("%d", &N);
    A = (ElementType *)malloc(sizeof(ElementType) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    // 调用排序函数
    // Bubble_Sort(A, N);
    // Insertion_Sort(A, N);
    // Shell_Sort(A, N);
    // Selection_Sort(A, N);
    Heap_Sort(A, N);

    // 输出结果
    printf("%d", A[0]);
    for (int i = 1; i < N; i++)
        printf(" %d", A[i]);

    free(A);
    return 0;
}

// 冒泡排序
void Bubble_Sort(ElementType A[], int N) {
    int temp, flag;
    for (int P = N - 1; P >= 0; P--) {
        flag = 0;
        for (int i = 0; i < P; i++) {
            if (A[i] > A[i + 1]) {
                // 将两个相邻元素进行交换
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                flag = 1;
            }
        }
        // 当一轮没有任何元素交换时，已经有序，直接退出
        if (flag == 0) break;
    }
}

// 插入排序
void Insertion_Sort(ElementType A[], int N) {
    int temp, j;
    for (int i = 1; i < N; i++) {
        // 保存要插入的值
        temp = A[i];
        // 向右挪出空位
        for (j = i; j > 0 && A[j - 1] > temp; j--)
            A[j] = A[j - 1];
        // 放置目标值
        A[j] = temp;
    }
}

// Sedgewick增量的希尔排序
void Shell_Sort(ElementType A[], int N) {
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
            temp = A[i];
            for (j = i; j >= D && A[j - D] > temp; j -= D)
                A[j] = A[j - D];
            A[j] = temp;
        }
    }
}

// 选择排序
void Selection_Sort(ElementType A[], int N) {
    int min, temp;
    for (int i = 0; i < N - 1; i++) {
        // 寻找从i到N-1的最小值
        min = i;
        for (int j = i + 1; j < N; j++)
            if (A[j] < A[min]) min = j;
        // 将第i个元素和最小值位置的元素交换
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

// 对输入堆的根节点r进行下滤操作
void Heap_Perc_Down(ElementType A[], int N, int R) {
    // 保存根节点的值
    int X = A[R], Parent, Child;
    for (Parent = R; Parent * 2 + 1 < N; Parent = Child) {
        Child = Parent * 2 + 1;  // 先指向左儿子
        // 让Child指向值较大的儿子
        if (Child + 1 < N && A[Child + 1] > A[Child])
            Child++;
        if (X >= A[Child])
            // 若目标值比较大的儿子还大，则退出
            break;
        else
            // 否则的话用较大的儿子取代父节点
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

// 堆排序
void Heap_Sort(ElementType A[], int N) {
    int temp;
    // 初始化建堆
    for (int R = (N - 2) / 2; R >= 0; R--)
        Heap_Perc_Down(A, N, R);
    // 堆的规模从N到1
    for (int P = N; P > 1; P--) {
        // 交换堆的根节点和最后一个节点
        temp = A[0];
        A[0] = A[P - 1];
        A[P - 1] = temp;
        // 对规模减一的堆进行根节点的调整
        Heap_Perc_Down(A, P - 1, 0);
    }
}