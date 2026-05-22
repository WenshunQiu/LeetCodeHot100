#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 205;
const int INF = 1000000000;

int n, m;
int g[MAXN][MAXN];
int dista[MAXN][MAXN];
int nxt[MAXN][MAXN];

vector<int> getPath(int u, int v)
{
    vector<int> path;
    if (nxt[u][v] == -1)
    {
        return path;
    }
    path.push_back(u);
    while (u != v)
    {
        u = nxt[u][v];
        path.push_back(u);
    }
    return path;
}

int main()
{
    freopen("in.txt", "r", stdin);
    if (scanf("%d %d", &n, &m) != 2)
    {
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                g[i][j] = 0;
                dista[i][j] = 0;
                nxt[i][j] = j;
            }
            else
            {
                g[i][j] = INF;
                dista[i][j] = INF;
                nxt[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (w < g[u][v])
        {
            g[u][v] = g[v][u] = w;
            dista[u][v] = dista[v][u] = w;
            nxt[u][v] = v;
            nxt[v][u] = u;
        }
    }

    int bestCost = INF;
    vector<int> bestCycle;

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i < k; i++)
        {
            for (int j = i + 1; j < k; j++)
            {
                if (g[i][k] == INF || g[k][j] == INF || dista[i][j] == INF)
                {
                    continue;
                }

                int cand = dista[i][j] + g[i][k] + g[k][j];
                if (cand < bestCost)
                {
                    vector<int> path = getPath(i, j);
                    if (!path.empty())
                    {
                        bestCost = cand;
                        bestCycle = path;
                        bestCycle.push_back(k);
                        bestCycle.push_back(i);
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            if (dista[i][k] == INF)
            {
                continue;
            }
            for (int j = 1; j <= n; j++)
            {
                if (dista[k][j] == INF)
                {
                    continue;
                }
                int cand = dista[i][k] + dista[k][j];
                if (cand < dista[i][j])
                {
                    dista[i][j] = cand;
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }

    if (bestCost == INF)
    {
        printf("It's impossible.\n");
        return 0;
    }

    printf("%d\n", bestCost);

    return 0;
}
