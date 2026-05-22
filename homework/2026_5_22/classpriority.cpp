#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define MAXV 5000
#define INF 32767
typedef int InfoType;

typedef struct ANode
{
    int adjvex;
    // 该边的邻接点编号
    struct ANode *nextarc;
    // 指向下一个点的指针
    int weight;
} ArcNode;
// 边结点的类型
typedef struct Vnode
{
    InfoType info;
    // 顶点的其他信息
    ArcNode *firstarc;
    // 指向第一个边结点
} VNode;
// 邻接表的头结点类型
typedef struct
{
    VNode adjlist[MAXV];
    // 邻接表的头结点数组
    int n, e;
    // 图中的顶点数n和边数e
} AdjGraph;

AdjGraph *CreateAG()
{
    AdjGraph *AG = (AdjGraph *)malloc(sizeof(AdjGraph));
    if (AG == nullptr)
    {
        return nullptr;
    }

    int n, e;
    if (scanf("%d %d", &n, &e) != 2)
    {
        free(AG);
        return nullptr;
    }

    AG->n = n;
    AG->e = e;

    for (int i = 0; i <= n; i++)
    {
        AG->adjlist[i].firstarc = nullptr;
    }
    for (int i = 0; i < e; i++)
    {
        int eA, eB;
        scanf("%d %d", &eA, &eB);
        ArcNode *ANa = (ArcNode *)malloc(sizeof(ArcNode));
        ANa->adjvex = eA;
        ANa->nextarc = AG->adjlist[eB].firstarc;
        AG->adjlist[eB].firstarc = ANa;
    }

    return AG;
} // 构建邻接表

int getPriority(AdjGraph *AG)
{
    // 一个入度表，一个priorityqueue，先存储入度，再将入度为0的入队伍，再一个while逐个取出输出并修改入度。
    int n = AG->n;
    int indegree[n] = {0};
    vector<int> order;
    priority_queue<int, vector<int>, greater<int>> qu;
    for (int i = 0; i < n; i++)
    {
        ArcNode *p = AG->adjlist[i].firstarc;
        while (p != nullptr)
        {
            int t = p->adjvex;
            indegree[t]++;
            p = p->nextarc;
        }
    } // 存储入度
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            qu.push(i);
        }
    } // 入度为0入队
    while (!qu.empty())
    {
        int t = qu.top();
        qu.pop();
        order.push_back(t);
        ArcNode *p = AG->adjlist[t].firstarc;
        while (p != nullptr)
        {
            int j = p->adjvex;
            indegree[j]--;
            if (indegree[j] == 0)
            {
                qu.push(j);
            }
            p = p->nextarc;
        }
    }
    if (order.size() != n)
    {
        printf("0\n");
        return 0;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", order[i]);
    }
    return 0;
}
int main()
{
    AdjGraph *AG;
    AG = CreateAG();
    getPriority(AG);
}