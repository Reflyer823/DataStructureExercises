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
void Merge_Sort1(ElementType A[], int N);
void Merge_Sort2(ElementType A[], int N);
void Quick_Sort(ElementType A[], int N);
void LSDRadix_Sort(ElementType A[], int N);

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
    // Heap_Sort(A, N);
    // Merge_Sort1(A, N);
    // Merge_Sort2(A, N);
    // Quick_Sort(A, N);
    LSDRadix_Sort(A, N);

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

// 对输入堆的根节点R进行下滤操作
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

// 对A中两个有序子列进行归并，输出到T中
void Merge(ElementType A[], ElementType T[], int start1, int start2, int end2) {
    int p1 = start1, p2 = start2, p = start1;
    // 每次选择两部分中较小的元素
    while (p1 < start2 && p2 <= end2) {
        if (A[p1] <= A[p2]) T[p++] = A[p1++];
        else T[p++] = A[p2++];
    }
    // 剩余部分全部进行拷贝
    while (p1 < start2) T[p++] = A[p1++];
    while (p2 <= end2) T[p++] = A[p2++];
} 

// 归并排序的递归函数
void MSort(ElementType A[], ElementType T[], int start, int end) {
    if (start >= end) return;
    int middle = (start + end) / 2;
    // 分别将左右半边排好序
    MSort(A, T, start, middle);
    MSort(A, T, middle + 1, end);
    // 对左右两个有序子列进行归并
    Merge(A, T, start, middle + 1, end);
    // 将归并后的数据从T中拷贝回A中
    for (int i = start; i <= end; i++)
        A[i] = T[i];
}

// 归并排序——递归实现
void Merge_Sort1(ElementType A[], int N) {
    ElementType *T = (ElementType *)malloc(sizeof(ElementType) * N);
    MSort(A, T, 0, N - 1);
    free(T);
}

// 对S中数据进行一轮Size大小的归并，输出到D中
void MSortRound(ElementType S[], ElementType D[], int N, int Size) {
    int I;
    // 每两个完整组进行一次归并
    for (I = 0; I + Size * 2 <= N; I += Size * 2)
        Merge(S, D, I, I + Size, I + Size * 2 - 1);
    // 当剩余两个组时，再归并一次；只剩一个组时，直接拷贝即可
    if (I + Size < N) Merge(S, D, I, I + Size, N - 1);
    else for (int i = I; i < N; i++) D[i] = S[i];
}

// 归并排序——非递归实现
void Merge_Sort2(ElementType A[], int N) {
    ElementType *T = (ElementType *)malloc(sizeof(ElementType) * N);
    // Size从1到大于等于N，每次循环做两轮，确保最后数据回到了A中
    for (int Size = 1; Size < N; Size *= 2) {
        MSortRound(A, T, N, Size);  // 从A归并到T
        Size *= 2;
        MSortRound(T, A, N, Size);  // 从T归并到A
    }
    free(T);
}

#define SWAP(X, Y) temp = (X); (X) = (Y); (Y) = temp

// 快速排序递归函数
void QSort(ElementType A[], int start, int end) {
    const int CUT_OFF = 300;
    // 当输入数据个数少于CUT_OFF时，直接采用插入排序
    if (end - start < CUT_OFF) {
        Insertion_Sort(A + start, end - start + 1);
        return;
    }
    // 选取主元
    int temp, middle = (start + end) / 2;
    if (A[start]  > A[middle]) {SWAP(A[start] , A[middle]);}
    if (A[middle] > A[end])    {SWAP(A[middle], A[end]   );}
    if (A[start]  > A[middle]) {SWAP(A[start] , A[middle]);}
    SWAP(A[middle], A[end - 1]);    // 将主元换到最右边来
    // 调整主元位置，划分左右子集
    int pivot = A[end - 1];
    int i = start, j = end - 1;
    for (; ; ) {
        while (A[++i] < pivot);
        while (A[--j] > pivot);
        if (i < j) {SWAP(A[i], A[j]);}
        else break;
    }
    SWAP(A[i], A[end - 1]);     // 将主元换到正确的位置上
    // 对左右子集分别递归调用快排
    QSort(A, start, i - 1);
    QSort(A, i + 1, end);
}

// 快速排序
void Quick_Sort(ElementType A[], int N) {
    QSort(A, 0, N - 1);
}

// 基数排序定义
#define RADIX 10
typedef struct LinkedListNode *LinkedList;
struct LinkedListNode {
    ElementType val;
    LinkedList next;
};
struct LinkedListHead {
    LinkedList head;
    LinkedList tail;
};
typedef struct LinkedListHead Bucket[RADIX];

// 基数排序——次位优先
void LSDRadix_Sort(ElementType A[], int N) {
    LinkedList L = NULL;
    Bucket B;
    // 创建并初始化每个桶
    for (int i = 0; i < RADIX; i++)
        B[i].head = B[i].tail = NULL;
    // 将原序列依次从头部插入一个链表中
    for (int i = 0; i < N; i++) {
        LinkedList new = (LinkedList)malloc(sizeof(struct LinkedListNode));
        new->val = A[i];
        new->next = L;
        L = new;
    }
    // 从最低位开始向高位，直到某一位全是0为止
    char flag = 1;
    LinkedList cur;
    int r;
    for (int d = 0; flag; d++) {
        // 分配，遍历整个链表并将每个元素分配到对应的桶中去
        flag = 0;
        while (L) {
            cur = L;
            L = L->next;
            cur->next = NULL;
            // 注意此处不能先对r求绝对值，否则在处理INT_MIN时取反会溢出
            r = cur->val;
            for (int i = 0; i < d; i++)
                r /= RADIX;
            // 当有一个元素更高的一位不是零时，置位flag
            if (r >= RADIX) flag = 1;
            r %= RADIX;
            // 对r取绝对值
            r = r < 0 ? -r : r;
            // 将cur这个节点插在第r个桶的末尾
            if (B[r].tail) {
                B[r].tail->next = cur;
                B[r].tail = cur;
            } else {
                B[r].head = B[r].tail = cur;
            }
        }
        // 收集，将每个桶内的元素按顺序合并为一个链表
        for (int i = RADIX - 1; i >= 0; i--) {
            // 跳过空的桶
            if (!B[i].head) continue;
            B[i].tail->next = L;
            L = B[i].head;
            B[i].head = B[i].tail = NULL;
        }
    }
    // 将正负数进行分离
    LinkedList last = NULL;
    cur = L;
    while (cur) {
        // 当遇到位置不在第一个的负数时，将其移动到链表头上去
        if (cur->val < 0 && last) {
            last->next = cur->next;
            cur->next = L;
            L = cur;
            cur = last->next;
        // 否则直接跳转到下一个元素
        } else {
            last = cur;
            cur = cur->next;
        }
    }
    // 将链表中的元素放回数组中，并释放空间
    int Ai = 0;
    while (L) {
        cur = L;
        L = L->next;
        A[Ai++] = cur->val;
        free(cur);
    }
}