#include "graph.hpp"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
int visited[MAXV] = {0};
// 下面的DFS和BFS需要以邻接表为存储结构
void DFS(AdjGraph *G, int v)
{
    ArcNode *p;
    visited[v] = 1;
    cout << v;
    p = G->adjlist[v].firstarc; // 指向v的第一个邻接点
    while (p != nullptr)
    {
        if (visited[p->adjvex] == 0)
        {
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}
void BFS(AdjGraph *G, int v)
{
    int w, i;
    ArcNode *p; // 临时存储点
    queue<int> qu;
    int visited[MAXV] = {0};
    cout << v;
    visited[v] = 1;
    qu.push(v);
    while (!qu.empty())
    {
        w = qu.front();
        qu.pop();
        p = G->adjlist[w].firstarc; // 找到第一个邻接点
        while (p != nullptr)        // 对p的每一个没有处理过的邻接点入队
        {
            if (visited[p->adjvex] == 0)
            {
                cout << p->adjvex;
                visited[p->adjvex] = 1;
                qu.push(p->adjvex);
            }
            p = p->nextarc; // 找到下一个邻接点
        }
    }
    cout << endl;
}
// 下面两个DFS1和BFS1是非连通图的遍历，本质上是将每个点按照原来的DFS/BFS遍历，只是用了一个visited数组来消除重复元素而已
void DFS1(AdjGraph *G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(G, i);
        }
    }
}
void BFS1(AdjGraph *G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)
        {
            BFS(G, i);
        }
    }
}
// 查询一个图是否联通
bool Connect(AdjGraph *G)
{
    bool flag = true;
    for (int i = 0; i < G->n; i++)
    {
        visited[i] = 0; // 初始化visited数组;
    }
    DFS(G, 0); // 选定一种遍历方式，确保可以遍历联通的地方
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

// 找到一条从u到v的路径,d为路径长度
void FindaPath(AdjGraph *G, int u, int v, int path[], int d)
{
    // d表示path中的路径长度，初始值应该为-1，使用内存序
    int w;
    ArcNode *p;
    visited[u] = 1;
    d++; // d是深度，需要每次递归的时候独立存储，不能&借用
    path[d] = u;
    if (u == v)
    {
        for (int i = 0; i < d + 1; i++)
        {
            printf("%d", path[i]);
        }
        printf("\n");
        return;
    }
    p = G->adjlist[u].firstarc; // 从u的第一个邻接点开始遍历
    while (p != nullptr)
    {
        w = p->adjvex; // 邻接点的编号为w
        if (visited[w] == 0)
        {
            FindaPath(G, w, v, path, d);
        }
        p = p->nextarc; // 指向下一个邻接点
    }
}
// 找到最近的陆地