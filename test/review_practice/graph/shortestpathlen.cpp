#include <bits/stdc++.h>
using namespace std;

// 从每个点开始bfs
// 三元组tuple存点，掩码，长度
// seen数组去重
int minpathlen(vector<vector<int>> &g)
{
    int gSize = g.size();
    queue<tuple<int, int, int>> q;
    vector<vector<int>> seen(gSize, vector<int>(1 << gSize, false));
    for (int i = 0; i < gSize; i++)
    {
        q.emplace(i, 1 << i, 0);
        seen[i][1 << i] = true;
    }
    int ans = 0;
    while (!q.empty())
    {
        auto [cur, mask, curLen] = q.front();
        q.pop();
        if (mask == (1 << gSize) - 1)
        {
            ans = curLen;
            return ans;
        }
        for (auto &&next : g[cur])
        {
            int nextMask = mask | (1 << next);
            if (seen[next][nextMask])
            {
                continue;
            }
            q.emplace(next, nextMask, curLen + 1);
            seen[next][nextMask] = true;
        }
    }
    return ans;
}