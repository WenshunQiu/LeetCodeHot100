#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<vector<int>> mat;
vector<vector<int>> dp;
vector<vector<vector<int>>> path;
int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
// 如果是图的遍历，我们就使用四个方向，这里的dfs需要传入x和y
// 如果是邻接表，直接使用forrange遍历，这里的dfs需要传入这个数字的值
pair<int, vector<int>> dfs(int x, int y)
{
    if (dp[x][y])
    {
        return {dp[x][y], path[x][y]};
    }
    int maxLen = 1;
    vector<int> bestSubPath;
    int cur = mat[x][y];
    for (int direction = 0; direction < 4; direction++)
    {
        int nextPlacex = x + dir[direction][0];
        int nextPlacey = y + dir[direction][1];
        if (nextPlacex >= 0 && nextPlacex < m && nextPlacey >= 0 && nextPlacey < n && mat[nextPlacex][nextPlacey] > cur)
        {
            auto [subLen, subPath] = dfs(nextPlacex, nextPlacey); // 从for开头到这里的顺序一般都是不变的，都是找四个方向然后进入
            if (subLen + 1 > maxLen)
            {
                maxLen = subLen + 1;
                bestSubPath = subPath;
            }
        }
    }
    dp[x][y] = maxLen;
    vector<int> res;
    res.push_back(cur);
    res.insert(res.end(), bestSubPath.begin(), bestSubPath.end());
    path[x][y] = res;
    return {maxLen, res};
}

int main()
{
    cin >> m >> n;
    mat.resize(m, vector<int>(n));
    dp.assign(m, vector<int>(n, 0));
    path.resize(m, vector<vector<int>>(n));
    // 构建这个图
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat[i][j];
        }
    }
    // 对每个点进行深度搜索
    int maxTotal = 0;
    vector<int> ans;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            auto [len, thispath] = dfs(i, j);
            if (len > maxTotal)
            {
                maxTotal = len;
                ans = thispath;
            }
        }
    }
    // 输出答案
    for (int i = 0; i < ans.size(); i++)
    {
        if (i > 0)
            cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;
}