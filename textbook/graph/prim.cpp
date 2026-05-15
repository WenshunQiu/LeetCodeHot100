#include "graph.hpp"
int Prim(MatGraph g, int v)
{
    int lowcost[MAXV];
    int mindist;
    int closest[MAXV], k;
    int res = v;
    for (int i = 0; i < g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    } // 设置初值
    for (int i = 0; i < g.n; i++)
    {
        mindist = INF;
        for (int j = 0; j < g.n; j++)
        {
            if (lowcost[j] != 0 && lowcost[j] < mindist)
            {
                mindist = lowcost[j];
                k = j; // k用来记录最近顶点的编号
            }
        }
        res += mindist;
        lowcost[k] = 0;               // 标记k已经加入了U
        for (int j = 0; j < g.n; j++) // 对剩下的顶点进行调整，重新设置它们的初值
        {
            if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j])
            {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;
            }
        }
    }
    return res;
}