#include <bits/stdc++.h>
using namespace std;
// 对每一个元素进行bfs，直到遍历完所有元素，使用mask标记所遍历过的元素
// 这里使用tuple，表示这个点，mask，路径长度；
// 对每个点进入队列，然后取出来遍历它的邻接表
class Solution
{
public:
    // 返回能输出所有节点的路径长度
    int shortestPathLength(vector<vector<int>> &graph)
    {

        int n = graph.size();
        queue<tuple<int, int, int>> q;
        vector<vector<int>> seen(n, vector<int>(1 << n, false));
        for (int i = 0; i < n; i++)
        { // 对每个点进入队列
            q.emplace(i, 1 << i, 0);
            seen[i][1 << i] = true;
        }
        while (!q.empty())
        {
            auto [u, mask, lenth] = q.front();
            q.pop();
            // 如果已经遍历完所有的节点，那就直接输出就可以了
            if (mask == (1 << n) - 1)
                return lenth;
            // 如果没有遍历完所有的节点，我们就把它的邻接点丢到q里面去
            for (int i = 0; i < graph[u].size(); i++)
            {
                int nu = graph[u][i];
                int nmask = mask | 1 << nu;
                if (!seen[nu][nmask])
                {
                    q.emplace(nu, nmask, lenth + 1);
                    seen[nu][nmask] = true;
                }
            }
        }
    }
};