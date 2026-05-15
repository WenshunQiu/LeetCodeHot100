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
// 先处理输入为正常的AdjGraph
// 再用prim,
// 图的点从1开始
// 建立无向图的邻接矩阵
void InputMakeMG(MatGraph *&MG)
{
    MG = (MatGraph *)malloc(sizeof(MatGraph));

    int n, e;
    scanf("%d %d", &n, &e);

    MG->n = n;
    MG->e = e;

    // 初始化邻接矩阵
    // 自己到自己为0，不相邻的点之间为INF
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                MG->edges[i][j] = 0;
            else
                MG->edges[i][j] = INF;
        }
    }

    int V, A, W;

    // 输入三元组
    // 题目中的顶点编号是1到n，数组下标是0到n-1，不是我喜欢的编号我不要，直接--
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &V, &A, &W);

        V--;
        A--;

        MG->edges[V][A] = W;
        MG->edges[A][V] = W;
    }
}

// 使用Prim算法求最小生成树的权值
int Prim(MatGraph g, int v)
{
    int lowcost[MAXV];  // lowcost[i]表示顶点i到当前生成树的最小边权
    int closest[MAXV];  // closest[i]表示顶点i连接到生成树中的哪个顶点
    bool visited[MAXV]; // visited[i]表示顶点i是否已经加入生成树

    memset(visited, false, sizeof(visited));

    int res = 0;

    // 初始化，从起点v开始
    for (int i = 0; i < g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    }

    visited[v] = true;

    // 还需要加入n-1个顶点
    for (int i = 1; i < g.n; i++)
    {
        int mindist = INF;
        int k = -1;

        // 找出未加入生成树且距离生成树最近的顶点
        for (int j = 0; j < g.n; j++)
        {
            if (!visited[j] && lowcost[j] < mindist)
            {
                mindist = lowcost[j];
                k = j;
            }
        }

        // 题目说明是连通图，正常不会出现k == -1，防止某些数据作妖
        if (k == -1)
        {
            return -1;
        }

        visited[k] = true;
        res += mindist;

        // 用新加入的顶点k更新其他未加入顶点的lowcost
        for (int j = 0; j < g.n; j++)
        {
            if (!visited[j] && g.edges[k][j] < lowcost[j])
            {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;
            }
        }
    }

    return res;
}//这个代码需要理解一下

int main()
{
    MatGraph *MG;

    InputMakeMG(MG);

    // 顶点编号虽然是1到n，但程序内部已经转成0到n-1
    // 所以从0号顶点开始Prim算法
    int ans = Prim(*MG, 0);

    printf("%d", ans);

    free(MG);

    return 0;
}