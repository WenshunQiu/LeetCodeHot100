#define MAX 100
typedef struct huffman
{
    char data;
    double weight;
    int parent;
    int lchild;
    int rchild;
} HTNode;
typedef struct HCode
{
    char cd[100];
    int start;
} HCode;
typedef struct BTNode
{
    char data;
    BTNode *lchild;
    BTNode *rchild;
} BTNode;