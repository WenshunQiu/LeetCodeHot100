#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) // 输入一个图
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    int count = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] != 1)
                continue;
            // 发现新岛屿，BFS 淹灭整个岛
            // 四个方向(for)，分别延伸，如果遇到陆地，就淹没并进入队列(queue)中(方便处理与之相邻的陆地)，然后继续出队，继续(while)查找四个方向
            count++;
            queue<pair<int, int>> q;
            q.push(make_pair(i, j));
            grid[i][j] = 0;
            while (!q.empty())
            {
                int r = q.front().first, c = q.front().second;
                q.pop();
                for (int d = 0; d < 4; d++)
                {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1)
                    {
                        grid[nr][nc] = 0;
                        q.push(make_pair(nr, nc));
                    }
                }
            }
        }
    }

    cout << count << endl;
    return 0;
}
