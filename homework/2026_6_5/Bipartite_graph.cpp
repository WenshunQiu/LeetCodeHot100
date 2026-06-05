#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <stack>
using namespace std;
#define MAX 105
typedef struct MatGraph
{
    int n;
    int edges[MAX][MAX];
} MatGraph;

void makeGraph(MatGraph *&g)
{
    g = new MatGraph();
    memset(g->edges, 0, sizeof(g->edges));
    scanf("%d", &g->n);

    for (int u = 0; u < g->n; u++)
    {
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; j++)
        {
            int v;
            scanf("%d", &v);
            g->edges[u][v] = 1;
        }
    }
}
int errorflag = 0;
void dyeGraph(MatGraph *&g)
{ // 给每一行标记，先看自己是否被标记，然后遍历这一行元素，如果被标记了那就不管，如果没有被标记那就标记为不同颜色[这里用数字表示]
    // 这里第101行为标记行
    stack<int> stk;
    stk.push(0);
    for (int i = 0; i < g->n; i++)
    {
        stk.push(i);
    }
    while (!stk.empty())
    {
        int a = stk.top();
        stk.pop();
        if (g->edges[101][a] == 0)
        {
            g->edges[101][a] = 2;
        }
        int printColor = g->edges[101][a] == 2 ? 3 : 2;
        for (int i = 0; i < g->n; i++)
        {
            if (g->edges[a][i] == 1 && g->edges[101][i] == 0)
            {
                // 如果是联通且未染色
                g->edges[101][i] = printColor;
                stk.push(i);
            }
            else if (g->edges[a][i] == 1 && g->edges[101][i] == g->edges[101][a])
            {
                errorflag = 1;
                return;
            }
        }
    }
}
int main()
{
    MatGraph *g;
    makeGraph(g);
    dyeGraph(g);
    if (errorflag)
    {
        printf("false");
        return 0;
    }
    printf("true");
}