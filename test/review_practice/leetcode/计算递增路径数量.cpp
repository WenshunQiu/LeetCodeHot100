#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countPaths(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<long long>> dp(m, vector<long long>(n, 1));
        vector<tuple<int, int, int>> cells; // 格子以及它的值;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cells.emplace_back(grid[i][j], i, j);
            }
        }
        // 类似于拓扑排序，先搞掉小的
        sort(cells.begin(), cells.end());
        long long ans = 0;
        for (auto &&t : cells)
        {
            // int val = get<0>(t);
            // int x = get<1>(t);
            // int y = get<2>(t);
            auto [val, x, y] = t;
            for (auto &&d : dirs)
            {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] < val)
                {
                    dp[x][y] = (dp[x][y] + dp[nx][ny]);
                }
            }
            ans = (ans + dp[x][y]) % mod;
        }
        return (int)ans;
    }

private:
    int mod = 1e9 + 7;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
};