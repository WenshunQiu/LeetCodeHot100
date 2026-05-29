#include <iostream>
#include <climits>
#include <cstdio>
#define MAX 10005
using namespace std;

typedef struct MatGraph
{
    int G[MAX][MAX];
    int n, e;
} MatGraph;

long long prim(MatGraph *G, int root)
{
    long long cost = 0;
    int lowcost[MAX];
    int closest[MAX];
    bool used[MAX] = {false};

    for (int i = 0; i < G->n; i++)
    {
        lowcost[i] = G->G[root][i];
        closest[i] = root;
    }
    lowcost[root] = 0;
    used[root] = true;

    // 还需要选 n-1 个点
    for (int j = 1; j < G->n; j++)
    {
        int realmin = INT_MAX;
        int realmindot = -1;

        for (int i = 0; i < G->n; i++)
        {
            if (!used[i] && lowcost[i] < realmin)
            {
                realmin = lowcost[i];
                realmindot = i;
            }
        }

        // 不连通
        if (realmindot == -1 || realmin == INT_MAX)
            return -1;

        used[realmindot] = true;
        cost += realmin;

        for (int i = 0; i < G->n; i++)
        {
            if (!used[i] && G->G[realmindot][i] < lowcost[i])
            {
                closest[i] = realmindot;
                lowcost[i] = G->G[realmindot][i];
            }
        }
    }
    return cost;
}

int main()
{
    int n, e;
    scanf("%d %d", &n, &e);

    MatGraph *G = new MatGraph;
    G->n = n;
    G->e = e;

    // 只初始化 n*n，避免无谓大循环
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) G->G[i][j] = 0;
            else G->G[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < e; i++)
    {
        int a, b, weight;
        scanf("%d %d %d", &a, &b, &weight);
        a--;
        b--;
        // 若有重边，取更小权值
        if (weight < G->G[a][b])
        {
            G->G[a][b] = weight;
            G->G[b][a] = weight;
        }
    }

    // 连通图的 MST 与起点无关，跑一次即可
    long long ans = prim(G, 0);
    printf("%lld\n", ans);

    delete G;
    return 0;
}
