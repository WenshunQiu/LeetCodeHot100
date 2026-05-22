#include <cstdio>

const int MAXN = 105;
const int INF = 1000000000;

int dista[MAXN][MAXN];

int main()
{
    freopen("in.txt", "r", stdin);

    int n;
    while (scanf("%d", &n) == 1)
    {
        // 边界检查
        if (n == 0)
        {
            break;
        }
        // 初始化图像
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dista[i][j] = (i == j ? 0 : INF);
            }
        }
        // 写入图像
        for (int i = 1; i <= n; i++)
        {
            int m;
            scanf("%d", &m);
            for (int k = 0; k < m; k++)
            {
                int to, w;
                scanf("%d %d", &to, &w);
                if (w < dista[i][to])
                {
                    dista[i][to] = w;
                }
            }
        }
        // Floyd算法
        for (int k = 1; k <= n; k++)
        {
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
                    }
                }
            }
        }
        // 找到最小就可以了
        int bestPerson = -1;
        int bestTime = INF;

        for (int i = 1; i <= n; i++)
        {
            int farthest = 0;
            bool ok = true;
            for (int j = 1; j <= n; j++)
            {
                if (dista[i][j] == INF)
                {
                    ok = false;
                    break;
                }
                if (dista[i][j] > farthest)
                {
                    farthest = dista[i][j];
                }
            }

            if (ok && farthest < bestTime)
            {
                bestTime = farthest;
                bestPerson = i;
            }
        }

        if (bestPerson == -1)
        {
            printf("disjoint\n");
        }
        else
        {
            printf("%d %d\n", bestPerson, bestTime);
        }
    }

    return 0;
}
