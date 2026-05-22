#define MAXI 100
typedef int KeyType;
typedef char InfoType;
// 线性表的查找与索引
typedef struct RecType
{
    KeyType key;
    InfoType data;
} RecType;
typedef struct IdxType
{
    KeyType key;
    int link;
} IdxType;
// 树的查找
typedef struct node
{
    KeyType key;
    InfoType data;
    struct node *lchild, *rchild;
} BSTNode;

