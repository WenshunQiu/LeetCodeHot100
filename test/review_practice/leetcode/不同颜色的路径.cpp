#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
    {
        // 先创建邻接表
        vector<vector<int>> redGraph(n), blueGraph(n);
        for (auto &&e : redEdges)
        {
            redGraph[e[0]].push_back(e[1]);
        }
        for (auto &&e : blueEdges)
        {
            blueGraph[e[0]].push_back(e[1]);
        }
        const int INF = INT_MAX;
        // dist[节点][0] : 当前点如果以红边结尾它的长度;
        vector<vector<int>> dist(n, vector<int>(2, INF));

        queue<pair<int, int>> q;
        dist[0][0] = 0;
        dist[0][1] = 0;
        q.emplace(0, 0);
        q.emplace(0, 1);
        while (!q.empty())
        {
            auto [u, color] = q.front();
            q.pop();
            int curLen = dist[u][color];
            // 如果是红色，那就检查蓝色邻接表
            if (color == 0)
            {
                for (auto &&v : blueGraph[u])
                {
                    if (dist[v][1] > curLen + 1)
                    {
                        dist[v][1] = curLen + 1;
                        q.emplace(v, 1);
                    }
                }
            }
            else
            {
                for (auto &&v : redGraph[u])
                {
                    if (dist[v][0] > curLen + 1)
                    {
                        dist[v][0] = curLen + 1;
                        q.emplace(v, 0);
                    }
                }
            }
        }
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++)
        {
            int minDis = min(dist[i][0], dist[i][1]);
            if (minDis != INF)
                ans[i] = minDis;
        }
        return ans;
    }
};