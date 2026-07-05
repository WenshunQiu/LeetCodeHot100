#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);
        for (auto &&e : edges)
        {
            int x = e[0];
            int y = e[1];
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        vector<int> visited(n);
        queue<int> q;
        q.emplace(source);
        visited[source] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &&nu : adj[u])
            {
                if (nu == destination)
                    return true;
                if (visited[nu])
                {
                    continue;
                }
                visited[nu] = true;
                q.push(nu);
            }
        }
        // 如果直接返回false的话，可能出错，采用比较稳妥的等义替换为visited[destination]即可解决
        /*
        n =
        1
edges =
[]
source =
0
destination =
0*/
        return visited[destination];
    }
};