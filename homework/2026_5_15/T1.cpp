#include <iostream>
using namespace std;
#define MVNum 100 // 最大顶点数
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int VerTexType; // 假设顶点的数据类型为整型
// 图的邻接矩阵存储表示
typedef struct
{
    VerTexType vexs[MVNum]; // 顶点表，用来存名称的
    int arcs[MVNum][MVNum]; // 邻接矩阵
    int vexnum, arcnum;     // 图的当前点数和边数
} AMGraph;
// 确定点v在G中的位置
int LocateVex(AMGraph G, VerTexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
}
// 采用邻接矩阵表示法，创建无向网G
int CreateUDN(AMGraph &G)
{
    printf("Please input the total number of vertices and the total number of edges, separated by a space:\nPlease input the names of the vertices, such as 1:\nPlease input the vertices to which the edge is attached, such as 1 2:\n\nThe adjacency matrix of the undirected network G is:\n");
    // 请补全代码
    int n, e;
    scanf("%d %d", &n, &e);
    G.vexnum = n;
    G.arcnum = e;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &G.vexs[i]);
    }
    // 初始化邻接矩阵为0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G.arcs[i][j] = 0;
        }
    }
    int V, N, Vp, Np;
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d", &V, &N);
        Vp = LocateVex(G, V);
        Np = LocateVex(G, N);
        // 检查顶点是否存在
        if (Vp != -1 && Np != -1)
        {
            G.arcs[Vp][Np] = 1;
            G.arcs[Np][Vp] = 1;
        }
    }
    return OK;
}
// 输出无向网G的邻接矩阵
void OutputAdjMatrix(AMGraph G)
{
    // 请补全代码
    int n = G.vexnum;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d  ", G.arcs[i][j]);
        }
        printf("\n");
    }
}
// 输出无向网G的各顶点的度
void OutputDegree(AMGraph G)
{
    int n = G.vexnum;
    for (int i = 0; i < n; i++)
    {
        int du = 0;
        for (int j = 0; j < n; j++)
        {
            if (G.arcs[i][j] == 1)
            {
                du++;
            }
        }
        printf("The degree of vertex %d is %d\n", G.vexs[i], du);
    }
}
int main()
{
    AMGraph G;
    CreateUDN(G);
    OutputAdjMatrix(G);
    OutputDegree(G);
    return 0;
}