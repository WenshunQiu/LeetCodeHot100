#define MAX 100
typedef int ElemType;
typedef struct huffman
{
    char data;
    double weight;
    int parent;
    int lchild;
    int rchild;
} HTNode; // 哈夫曼树
typedef struct HCode
{
    char cd[100];
    int start; // 表示cd[start..n0]是哈夫曼编码
} HCode;       // 哈夫曼编码
// 这里所表示的哈夫曼树其实是存储在二叉链当中的，即一个用2*n(左子树),2*n+1(右子树)查找的数组中
typedef struct BTNode
{
    char data;
    BTNode *lchild;
    BTNode *rchild;
} BTNode; // 树的节点
typedef struct node
{
    ElemType data;
    int ltag, rtag;
    struct node *lchild;
    struct node *rchild;

} TBTNode; // 线索二叉树
