#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    int compCount = 0, maxSize = 0;

    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        compCount++;
        int size = 0;
        queue<int> q;
        q.push(i);
        vis[i] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            size++;
            for (int v : adj[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        maxSize = max(maxSize, size);
    }

    cout << compCount << " " << maxSize << endl;
    return 0;
}
