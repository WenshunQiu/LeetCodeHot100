#include "graph.hpp"
#include <cstdlib>
using namespace std;
void CreateAdj(AdjGraph *&G, int A[MAXV][MAXV], int n, int e)
{
    ArcNode *p;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    for (int i = 0; i < n; i++)
    {
        G->adjlist[i].firstarc = nullptr;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (A[i][j] != 0 && A[i][j] != INF)
            {
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j; // 存放邻接点
                p->weight = A[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
            }
        }
    }
    G->n = n;
    G->e = e;
}