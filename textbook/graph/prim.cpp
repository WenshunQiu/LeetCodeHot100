#include "graph.hpp"
#include <iostream>
void Prim(MatGraph g, int v)
{
    int lowcost[MAXV];
    int mindest;
    int closest[MAXV];
    int k;
    // 目的：对于每一次构建的树，找到它的最短临边，并确定它是由哪个点构成的临边；
    for (int i = 0; i < g.n; i++) // 从v点开始标记它的临边以及weight
    {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    }

    for (int i = 0; i < g.n; i++)
    {
        mindest = INF;
        for (int j = 0; j < g.n; j++) // 找到weight最小的边
        {
            if (lowcost[j] != 0 && lowcost[j] < mindest)
            {
                mindest = lowcost[j];
                k = j; // 标记最短的那条边
            }
        }
        printf("(%d,%d):%d", closest[k], k, mindest); // 这里连接顺序是从根连接到叶子节点
        lowcost[k] = 0;                               // 表示这个点已经被连接了
        // 连接了新的节点，变化的应该是新节点连接状态，更新最小的即可
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