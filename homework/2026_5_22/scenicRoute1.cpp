#include <cstdio>
#include <algorithm>
#define MAXN 205
#define INF 25526
using namespace std;

int dist[MAXN][MAXN];
int edges[MAXN][MAXN];

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, e;
    scanf("%d %d", &n, &e);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                dist[i][j] = 0;
                edges[i][j] = 0;
            }
            else
            {
                edges[i][j] = INF;
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < e; i++)
    {
        int dot1, dot2, weight;
        scanf("%d %d %d", &dot1, &dot2, &weight);
        dot1--;
        dot2--;
        dist[dot1][dot2] = weight;
        dist[dot2][dot1] = weight;
        edges[dot1][dot2] = weight;
        edges[dot2][dot1] = weight;
    }
    int start = -1;
    int minway = INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            for (int k = j + 1; k < n; k++)
            {
                if (i == k || edges[j][i] == INF || edges[i][k] == INF || dist[j][k] == INF)
                {
                    continue;
                }
                int len = dist[j][k] + edges[j][i] + edges[i][k];
                if (len < minway)
                {
                    minway = len;
                    start = j;
                }
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            for (int k = 0; k < n; k++)
            {
                if (k == i)
                {
                    continue;
                }
                int len1 = dist[j][i] + dist[i][k];
                if (len1 < dist[j][k])
                {
                    dist[j][k] = len1;
                }
            }
        }
    }
    if (minway != INF)
    {
        // printf("%d %d\n", start + 1, minway);
        printf("%d\n", minway);
    }
    else
    {
        printf("It's impossible.\n");
    }
}