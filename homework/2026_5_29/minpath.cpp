#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
using namespace std;

typedef struct MatGraph
{
    vector<vector<int>> G;
    int n, e;
} MatGraph;

long long prim(MatGraph *G, int root)
{
    vector<int> lowcost(G->n, INT_MAX);
    vector<int> vis(G->n, 0);
    long long cost = 0;
    lowcost[root] = 0;

    for (int i = 0; i < G->n; i++) {
        int u = -1;
        int mn = INT_MAX;
        for (int j = 0; j < G->n; j++) {
            if (!vis[j] && lowcost[j] < mn) {
                mn = lowcost[j];
                u = j;
            }
        }
        if (u == -1) return -1; // Í¼²»Á¬Í¨
        vis[u] = 1;
        cost += mn;

        for (int v = 0; v < G->n; v++) {
            if (!vis[v] && G->G[u][v] < lowcost[v]) {
                lowcost[v] = G->G[u][v];
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
    G->G.assign(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) G->G[i][i] = 0;

    for (int i = 0; i < e; i++)
    {
        int a, b, weight;
        scanf("%d %d %d", &a, &b, &weight);
        a--;
        b--;
        if (weight < G->G[a][b]) {
            G->G[a][b] = weight;
            G->G[b][a] = weight;
        }
    }

    long long realMinCost = prim(G, 0);
    printf("%lld\n", realMinCost);
}
