#include <iostream>
#include <stack>
#include "textbook/graph/graph.hpp"
#define MAX 1001
using namespace std;

int visited[MAX] = {0};
// u是现在的点,v是目标的点
void FindAllPath(AdjGraph *g, int u, int v, int path[], int d)
{
    int w;
    ArcNode *p;
    path[d++] = u;  // 添加入路径
    visited[u] = 1; // 表示已经访问过了
    if (u == v)
    {
        for (int i = 0; i <= d; i++) // 这个是使用小于还是小于等于，怎么好理解怎么来吧
        {
            printf("%2d", path[i]);
        }
        printf("\n");
        visited[u] = 0; // 恢复终点可见性
        return;
    }
    p = g->adjlist[u].firstarc;
    while (p != nullptr)
    {
        w = p->adjvex;
        if (visited[w] == 0)
        {
            FindAllPath(g, w, v, path, d); // 对于没有访问过的点，递归访问
        }
        p = p->nextarc;
    }
    visited[u] = 0; // 恢复环境,让其可以正常回溯
}

struct Frame
{
    int u;
    ArcNode *p;
};
// 思路是从一个点开始一直遍历它的第一个邻接点(while)，如果遍历完，那就回溯一个(pop)，从上一个(stack)继续遍历邻接点(邻接点的visited)
void FindAllPath(AdjGraph *g, int u, int v)
{
    stack<Frame> st;
    int path[MAX] = {0};
    int d = -1; // 当前的路径

    st.push({u, g->adjlist[u].firstarc});
    visited[u] = 1;
    path[++d] = u;
    while (!st.empty())
    {
        Frame &top = st.top(); // 借用，直接修改
        int cur = top.u;

        if (cur == v)
        {
            for (int i = 0; i <= d; i++)
            {
                cout << path[i] << " ";
            }
            cout << endl;
            visited[cur] = 0;
            st.pop();
            d--;
            continue;
        }
        while (top.p != nullptr && visited[top.p->adjvex] == 1)
        {
            top.p = top.p->nextarc; // 指向下一个连接的点
        } // 跳过已经访问的点
        if (top.p != nullptr)
        { // 进入下一层
            int w = top.p->adjvex;
            top.p = top.p->nextarc;
            st.push({w, g->adjlist[w].firstarc});
            visited[w] = 1;
            path[++d] = w;
        }
        else
        { // 如果所有的邻接点都遍历完了，那就回溯
            visited[cur] = 0;
            st.pop();
            d--;
        }
    }
}