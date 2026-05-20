#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define MAX_VERTEX_NUM 100
typedef int Status;
typedef char VertexType;
typedef double VRType;
typedef int InfoType;
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind; // 图类型 有向图， 有向网，无向图，无向网
typedef struct ArcNode
{                            // 表结点
    int adjvex;              // 该弧所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条弧的指针
} ArcNode;
typedef struct VNode
{
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一个表结点
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum; // 顶点数和边数
    int kind;           // 图的种类标志
} ALGraph;
// 若G中存在顶点v 返回v的位置 否则返回-1.
int LocateVex(ALGraph G, VertexType v)
{
    // 若G中存在顶点v 返回v的位置 否则返回-1
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == v)
            return i;
    }
    return -1;
}
// 无向图
void CreateUDG(ALGraph &G)
{
    int i;
    // 1.输入顶点数和边数
    printf("please input the vexnum and arcnum\n");
    printf("vexnum=\n");
    scanf("%d", &G.vexnum);
    printf("arcnum=\n");
    scanf("%d", &G.arcnum);
    printf("\n");
    // 2.顶点表数据域填值初始化顶点表指针域
    printf("enter the vexdata\n");
    for (i = 0; i < G.vexnum; i++)
    {
        scanf(" %c", &G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }
    printf("\n");
    // 3.输入边信息构造邻接表
    int n, m;
    VertexType v1, v2;
    ArcNode *p1, *p2;
    printf("enter the edge\n");
    for (i = 0; i < G.arcnum; i++)
    { // 输入边信息，并确定v1和v2在G中的位置，即顶点在AdjList[]数组中的位置（下标）
        printf("input %d edge:", i + 1);
        scanf(" %c%c", &v1, &v2);
        n = LocateVex(G, v1);
        m = LocateVex(G, v2);
        if (n == -1 || m == -1)
        {
            printf("NO This Vertex!\n");
            return;
        }
        p1 = (ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex = m;                       // 填上坐标
        p1->nextarc = G.vertices[n].firstarc; // 改链（头插法）
        G.vertices[n].firstarc = p1;
        p2 = (ArcNode *)malloc(sizeof(ArcNode)); // 无向图的对称
        p2->adjvex = n;
        p2->nextarc = G.vertices[m].firstarc;
        G.vertices[m].firstarc = p2;
    } // for
    G.kind = UDG;
}
// 返回G中 v顶点的第一个邻接点 若没有返回-1.
int FirstAdjVex(ALGraph G, VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 返回v的第一个邻接顶点的序号。
    // 若顶点在G中没有邻接顶点,则返回-1
    ArcNode *p;
    int v1;
    v1 = LocateVex(G, v); // v1为顶点v在图G中的序号
    p = G.vertices[v1].firstarc;
    if (p)
        return p->adjvex;
    else
        return -1;
}
// 返回G中 w是v顶点的一个邻接点 返回v的邻接点w后下一个邻接点 若w是最后一个邻接点 返回-1.
int NextAdjVex(ALGraph G, VertexType v, VertexType w)
{ // 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
    // 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。
    // 若w是v的最后一个邻接点,则返回-1
    //*****补齐代码
    ArcNode *p = G.vertices[LocateVex(G, w)].firstarc;
    while (p->adjvex != v)
    {
        p = p->nextarc;
    }
    return LocateVex(G, p->adjvex);
}
int visited[MAX_VERTEX_NUM];
void DFS(ALGraph G, int v)
{
    ArcNode *p = G.vertices[v].firstarc;
    visited[v] = 1;
    printf("%c ", G.vertices[v].data);
    while (p != nullptr)
    {
        int v = p->adjvex;
        if (visited[v] == 0)
        {
            DFS(G, v);
        }
        p = p->nextarc;
    }
    //*****补齐代码
}
// 判断图中两个顶点是否连通
void isConnected(ALGraph G, int v1, int v2, int &flag)
{
    //*****补齐代码
    if (flag)
    {
        return;
    }
    if (v1 == v2)
    {
        flag = true;
        return;
    }
    ArcNode *p = G.vertices[v1].firstarc;
    visited[v1] = 1;
    while (p != nullptr)
    {
        int v = p->adjvex;
        if (visited[v] == 0)
        {
            isConnected(G, v, v2, flag);
        }
        p = p->nextarc;
    }
}
void print(ALGraph G)
{
    int i;
    ArcNode *p;
    printf("\n-------------------------------\n");
    for (i = 0; i < G.vexnum; i++)
    {
        printf("\n   AdjList[%d]%4c", i, G.vertices[i].data);
        p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            printf("-->%d", p->adjvex);
            p = p->nextarc;
        }
    }
    printf("\n");
}
int main()
{
    //
    ALGraph G;
    CreateUDG(G);
    int n1, n2;
    scanf("%d %d", &n1, &n2); // 输入n1 n2，用于后续判断是否连通
    printf("\n");
    print(G);
    int i;
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        visited[i] = FALSE;
    DFS(G, 0);
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        visited[i] = FALSE;
    int flag = FALSE;
    isConnected(G, n1, n2, flag);
    if (flag == TRUE)
    {
        printf("\n%d %d connect\n", n1, n2);
    }
    else
    {
        printf("\n%d %d unconnect\n", n1, n2);
    }
    return 0;
}
