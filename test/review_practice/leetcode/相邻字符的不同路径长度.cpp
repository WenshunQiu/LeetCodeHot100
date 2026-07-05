#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 作为一个图来解决
    // dfs一下，把每个邻接点都dfs一下，传入下去的有[下个节点和当前节点的值]用来判断会不会重复
    int longestPath(vector<int> &parent, string s)
    {
        adj.resize(parent.size());
        // 创建无向图的邻接表
        for (int i = 1; i < parent.size(); i++)
        {
            adj[i].emplace_back(parent[i]);
            adj[parent[i]].emplace_back(i);
        }
        this->s = s;
        dfs(0, -1);
        return ans;
    }

private:
    vector<vector<int>> adj;
    string s;
    int maxLenth = 0;
    int ans = 0;
    // 每个点需要做的是dfs它的下一个点，以及返回最长的长度，dfs的时候要走不是父亲的路和不是相同字符的路
    int dfs(int u, int father)

    {
        int firstLen = 0, secondLen = 0;
        for (auto &&nu : adj[u])
        {
            if (nu == father)
                continue; // 不要倒回去了
            int childLen = dfs(nu, u);
            if (s[u] == s[nu])
                continue; // 如果相等就不走
            if (childLen > firstLen)
            {
                secondLen = firstLen;
                firstLen = childLen;
            }
            else if (childLen > secondLen)
            {
                secondLen = childLen;
            }
        }
        ans = max(ans, firstLen + secondLen);
        // 更新最长的长度
        return firstLen + 1; // 返回的是一条路的数值
    }
};