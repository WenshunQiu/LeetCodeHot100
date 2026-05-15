#define MAXV 1000
#define INF 32767
typedef int InfoType;
typedef struct
{
    int no;
    InfoType info;
} VertexType;
typedef struct
{
    int edges[MAXV][MAXV];
    int n, e;
    VertexType vexs[MAXV];
} MatGraph;
typedef struct ANode
{
    int adjvex;
    // 该边的邻接点编号
    struct ANode *nextarc;
    // 指向下一个点的指针
    int weight;
} ArcNode;
// 边结点的类型
typedef struct Vnode
{
    InfoType info;
    // 顶点的其他信息
    ArcNode *firstarc;
    // 指向第一个边结点
} VNode;
// 邻接表的头结点类型

typedef struct
{
    VNode adjlist[MAXV];
    // 邻接表的头结点数组
    int n, e;
    // 图中的顶点数n和边数e
} AdjGraph;
// 完整的图邻接表类型
// 每个点都是头节点，头节点(Vnode)不是邻接点(ArcNode/ANode)！，头节点(VNode)保存指向第一个邻接点(ANode)的指针，
// 而在这个邻接点(ANode)内又保存了指向下一个之前头节点(ANode)的另一个邻接点(ANode)的指针.