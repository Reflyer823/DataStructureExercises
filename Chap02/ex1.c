#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ) {
    List LV1 = L1->Next, LV2 = L2->Next;
    List L = (List)malloc(sizeof(struct Node));
    List LV = L;
    while (LV1 && LV2) {
        if (LV1->Data <= LV2->Data) {
            LV->Next = LV1;
            LV1 = LV1->Next;
        } else {
            LV->Next = LV2;
            LV2 = LV2->Next;
        }
        LV = LV->Next;
    }
    if (LV1) LV->Next = LV1;
    else LV->Next = LV2;
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}