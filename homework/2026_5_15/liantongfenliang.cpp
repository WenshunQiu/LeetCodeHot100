#include <iostream>
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

void CreateAdj(AdjGraph *&AG, MatGraph *MG)
{
    AG = (AdjGraph *)malloc(sizeof(AdjGraph));
    int n = MG->n;
    int e = 0;
    for (int i = 0; i < n; i++)
    {
        AG->adjlist[i].firstarc = nullptr;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > -1; j--)
        {
            if (MG->edges[i][j] != 0 && MG->edges[i][j] != INF)
            {
                e++;
                ArcNode *AN = (ArcNode *)malloc(sizeof(ArcNode));
                AN->adjvex = j;
                AN->weight = MG->edges[i][j];
                AN->nextarc = AG->adjlist[i].firstarc;
                AG->adjlist[i].firstarc = AN;
            }
        }
    }
    AG->n = n;
    AG->e = e;
}
int visited[MAXV] = {0};
void DFS(AdjGraph *G, int k)
{
    ArcNode *p = G->adjlist[k].firstarc;
    visited[k] = 1;
    while (p != nullptr)
    {
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}
bool isAll(AdjGraph *G, int &leftout)
{
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0) // 如果存在0，则说明没有完全遍历
        {
            leftout = i;
            return false;
        }
    }
    leftout = -1; //-1表示已经完全遍历
    return true;
}
int main()
{
    MatGraph *MG = (MatGraph *)malloc(sizeof(MatGraph));

    scanf("%d", &MG->n);
    if (MG->n <= 0)
    {
        printf("%d", 0);
    }

    for (int i = 0; i < MG->n; i++)
    {
        for (int j = 0; j < MG->n; j++)
        {
            scanf("%d", &MG->edges[i][j]);
        }
    }
    // for (int i = 0; i < MG->n; i++)
    // {
    //     for (int j = 0; j < MG->n; j++)
    //     {
    //         printf("%d", MG->edges[i][j]);
    //     }
    //     printf("\n");
    // }
    AdjGraph *G;
    CreateAdj(G, MG);
    int leftout = 0;
    int times = 1;
    DFS(G, leftout);
    isAll(G, leftout);
    while (leftout != -1)
    {
        DFS(G, leftout); // 是不是0的一定有呢？
        isAll(G, leftout);
        times++;
    }
    printf("%d", times);
}
