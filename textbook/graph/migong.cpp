#include <iostream>
#include <vector>
#include <stack>
using namespace std;
const int maze[12][12] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; //(1,1) 出发到 (10,10)

int dfs(const int m[12][12], int x, int y, vector<pair<int, int>> &ans, int visited[12][12]) // 使用cpp记得如果要修改数据就要&借用！
{
    if (x == 10 && y == 10)
    {
        ans.push_back({10, 10});
        return true;
    }
    if (m[x][y] == 1 || visited[x][y] == 1) // 如果遇到墙或者已经走过了
    {
        return false;
    }
    if (x > 12 || x < 1 || y > 12 || y < 1) // 如果超出范围
    {
        return false;
    }

    ans.push_back({x, y});
    // 两种移动方向
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    visited[x][y] = 1; // 设置已经走过了
    for (int i = 0; i < 4; i++)
    {
        if (dfs(m, x + dx[i], y + dy[i], ans, visited))
        {

            return true;
        }
    }
    // 运行到这里说明这条路没得走
    ans.pop_back();    // 这条路是死路
    visited[x][y] = 0; // 往后退
    return false;
}

void printans(vector<pair<int, int>> ans)
{
    if (ans.size() == 0)
    {
        cout << "no answer" << endl;
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << '(' << ans[i].first << ',' << ans[i].second << ')' << "  ";
    }
}

// 已知一个位置，一个答案输出，一个已经经过的路径，一个迷宫
int solve(const int maze[12][12])
{
    vector<pair<int, int>> ans;
    int visited[12][12] = {0};
    dfs(maze, 1, 1, ans, visited);
    printans(ans);
    return 0;
}

int solve2(){
    stack<pair<int,int>> stk;
    vector<pair<int, int>> ans;
    int visited[12][12] = {0};
    
    
    return 0;
}
int main()
{
    solve(maze);
}