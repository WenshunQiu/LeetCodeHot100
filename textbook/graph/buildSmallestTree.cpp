#include "graph.hpp"
#include <iostream>

// Prim算法：从起点v出发，每次选一条连接“当前生成树”和“未加入顶点”的最小边
void Prim(MatGraph g, int v)
{
    int lowcost[MAXV]; // lowcost[j]：当前生成树到顶点j的最小边权；为0表示j已在树中
    int mindist;       // 本轮要选的最小边权
    int closest[MAXV]; // closest[j]：使lowcost[j]取最小值的树内顶点，也就是lowcost[j]取值对应的点
    int k;             // 本轮选中的新顶点

    // 初始化：先把v看作生成树，其他顶点到树的代价就是v到它们的边权
    for (int i = 0; i < g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    }

    // 迭代扩展生成树（通常会有效加入n-1条边）
    for (int i = 0; i < g.n; i++)
    {
        mindist = INF;

        // 在未入树顶点中，找到lowcost最小的顶点k
        for (int j = 0; j < g.n; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < mindist)
            {
                mindist = lowcost[j];
                k = j;
            }
        }

        // 输出本轮选中的边（对应最小生成树的一条边）
        printf("边(%d,%d)权为:%d\n", closest[k], k, mindist); // 这里是从未连接节点连接到已连接节点，它的连接顺序是从叶子连接到根

        // 标记k已加入生成树
        lowcost[k] = 0;

        // 用新加入的顶点k，尝试更新其他未入树顶点的最小连接代价
        for (int j = 0; j < g.n; j++)
        {
            if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j])
            {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;
            }
        }
    }
}
typedef struct Edge
{
    int u, v, w; // 边的起点，终点，以及权值
} Edge;

// 直接插入排序：按边权w从小到大排序
void InsertSort(Edge E[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Edge tmp = E[i];
        int j = i - 1;
        while (j >= 0 && E[j].w > tmp.w) // 在i左边并比选定tmp大的都右移
        {
            E[j + 1] = E[j];
            j--;
        }
        E[j + 1] = tmp;
    }
}

// Kruskal算法：每次选当前最小边，若两端点不在同一连通分量则加入生成树
void Kruskal(MatGraph g)
{
    int u1, v1, sn1, sn2, k;
    int vset[MAXV]; // vset[i]记录顶点i所在的连通分量编号
    Edge E[MAXV];   // 存放图中的边（无向图只取下三角，避免重复）
    k = 0;          // 当前已收集的边数

    // 1) 收集所有边到E中
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (g.edges[i][j] != 0 && g.edges[i][j] != INF)
            {
                E[k].u = i;
                E[k].v = j;
                E[k].w = g.edges[i][j];
                k++;
            }
        }
    }

    // 2) 按边权从小到大排序
    InsertSort(E, k);

    // 3) 初始化：每个顶点自成一个连通分量
    for (int i = 0; i < g.n; i++)
    {
        vset[i] = i;
    }

    // cnt表示当前已选入最小生成树的边数，MST最终需要n-1条边
    int cnt = 0;
    int j = 0; // 按排序后的边依次尝试

    // 4) 逐边尝试：若不构成回路则选入，并合并两个分量
    while (cnt < g.n - 1 && j < k)
    {
        u1 = E[j].u;
        v1 = E[j].v;
        sn1 = vset[u1];
        sn2 = vset[v1];
        if (sn1 != sn2)
        {
            printf("(%d,%d):%d\n", u1, v1, E[j].w);
            cnt++;
            for (int i = 0; i < g.n; i++)
            {
                if (vset[i] == sn2)
                {
                    vset[i] = sn1;
                }
            }
        }
        j++;
    }
}
