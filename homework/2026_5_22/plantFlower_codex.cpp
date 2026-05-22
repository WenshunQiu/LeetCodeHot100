#include <cstdio>
#include <vector>

int main()
{
    int n, m;
    if (scanf("%d %d", &n, &m) != 2)
    {
        return 0;
    }

    std::vector<std::vector<int>> g(n + 1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    std::vector<int> color(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        bool used[5] = {false, false, false, false, false};
        for (int v : g[i])
        {
            if (color[v] >= 1 && color[v] <= 4)
            {
                used[color[v]] = true;
            }
        }

        for (int c = 1; c <= 4; c++)
        {
            if (!used[c])
            {
                color[i] = c;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
        {
            printf(" ");
        }
        printf("%d", color[i]);
    }
    printf("\n");

    return 0;
}
