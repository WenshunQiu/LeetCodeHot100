#include "graph.hpp"
#include <stack>
#include <queue>
#include <iostream>
using namespace std;
void TopSort(AdjGraph *G) // 拓扑排序
{
    stack<int> stk;
    int indegree[MAXV];
    for (int i = 0; i < G->n; i++)
    {
        indegree[i] = 0;
    }
    for (int i = 0; i < G->n; i++) // 计算每个顶点的入度
    {
        ArcNode *p = G->adjlist[i].firstarc;
        while (p != nullptr)
        {
            int w = p->adjvex;
            indegree[w]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < G->n; i++) // 将入度为0的顶点入栈
    {
        if (indegree[i] == 0)
        {
            stk.push(i);
        }
    }
    while (!stk.empty()) // 循环处理
    {
        int t = stk.top();
        stk.pop();
        cout << t << " ";
        ArcNode *p = G->adjlist[t].firstarc;
        while (p != nullptr)
        {
            int w = p->adjvex;
            indegree[w]--;
            if (indegree[w] == 0)
            {
                stk.push(w);
            }
            p = p->nextarc;
        }
    }
}