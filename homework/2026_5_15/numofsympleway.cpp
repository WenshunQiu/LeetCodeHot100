#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
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
void InputMakeAdjG(AdjGraph *&G, int &start, int &len)
{
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    int n, e;
    scanf("%d %d %d %d", &n, &e, &start, &len);
    start--;
    G->n = n;
    G->e = e;
    for (int i = 0; i < n; i++)
    {
        G->adjlist[i].firstarc = nullptr;
    }
    int V, A; // 这里存放头和子
    ArcNode *p;
    for (int i = 0; i < e; i++)
    {
        p = (ArcNode *)malloc(sizeof(ArcNode));
        scanf("%d %d", &V, &A);
        V--;
        A--;
        p->adjvex = A;
        p->weight = 1;
        p->nextarc = G->adjlist[V].firstarc;
        G->adjlist[V].firstarc = p;
    }
}
int visited[MAXV] = {0};
void DFS(AdjGraph *G, int start, int deep, int len, int &ways)
{ // 首先传入的ways必须是0,deep也是0
    // printf("现在是%d，第%d层\n", start,deep);
    if (deep == len)
    {
        ways++;
        return;
    }
    ArcNode *p;
    p = G->adjlist[start].firstarc;
    visited[start] = 1;
    deep++;
    while (p != nullptr)
    {
        int vex = p->adjvex;
        if (visited[vex] == 0)
        {
            DFS(G, vex, deep, len, ways);
        }
        p = p->nextarc;
    }
    visited[start] = 0;
}
int main()
{
    AdjGraph *G;
    int start, len;
    InputMakeAdjG(G, start, len);
    int deep = 0;
    int ways = 0;
    DFS(G, start, deep, len, ways);
    printf("%d", ways);
}