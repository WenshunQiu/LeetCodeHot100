#include <bits/stdc++.h>
using namespace std;

const int MAXN = 26;
bool adj[MAXN][MAXN];
int color[MAXN];
int n;

bool dfs(int current, int colorsnum)
{
    if (current == n)
        return true;

    for (int currentcolor = 0; currentcolor < colorsnum; currentcolor++)
    {
        bool ok = true;
        for (int neighbor = 0; neighbor < n; neighbor++)
        {
            if (adj[current][neighbor] && color[neighbor] == currentcolor)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            color[current] = currentcolor;
            if (dfs(current + 1, colorsnum))
            {
                return true;
            }
            color[current] = -1;
        }
    }
    return false;
}

int main()
{
    memset(adj, 0, sizeof(adj));

    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);
        if (s.empty())
        {
            i--;
            continue;
        }

        int uindex = s[0] - 'A';
        for (int j = 2; j < (int)s.size(); j++)
        {
            if (!isupper(static_cast<unsigned char>(s[j])))
                continue;
            int vindex = s[j] - 'A';
            adj[uindex][vindex] = true;
            adj[vindex][uindex] = true;
        }
    }

    int ans = 4;
    for (int k = 1; k <= 4; k++)
    {
        memset(color, -1, sizeof(color));
        if (dfs(0, k))
        {
            ans = k;
            break;
        }
    }

    printf("%d", ans);
    return 0;
}
