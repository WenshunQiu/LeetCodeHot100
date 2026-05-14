#define MAXSIZE 100
#define ERROR -1
#define OK 1
#define FALSE 0
typedef int ElemType;

typedef struct SqList
{
    ElemType data[MAXSIZE];
    int length;
} SqList;
void InitList(SqList *L);
void CreateList(SqList *L, ElemType a[], int n);
void DestroyList(SqList *L);
int ListEmpty(SqList *L);
void ListLength(SqList *L);
void DispList(SqList *L);
void GetItem(SqList *L, int i, ElemType *e);
int LocateElem(SqList *L, ElemType e);
int ListInsert(SqList *L, int i, ElemType e);
int ListDelete(SqList *L, int i, ElemType *e);