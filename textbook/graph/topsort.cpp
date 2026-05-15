#include "graph.hpp"
#include <stack>
#include <queue>
#include <iostream>
using namespace std;
void TopSort(AdjGraph *G) // 拓扑排序
{
    // 这里一直变化的元素是每个节点入度，用一个数组indegree存储，
    // 其次对于入度为0的元素，我们需要依次把它们取用，可以用栈或者队列存储，
    // 每次处理一个节点，就要把它指向节点的入度减一，这个节点的入度为0了，那就要给它入栈/队列，
    // 取出下一个元素，继续处理，反复处理上面的操作.
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