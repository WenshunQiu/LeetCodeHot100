#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int x, y;
};
int main()
{
    int n, m;
    cin >> n >> m;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }
    x1--;
    y1--;
    x2--;
    y2--;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<Node>> pre(n, vector<Node>(m, {-1, -1}));
    queue<Node> q;
    q.push({x1, y1});
    dist[x1][y1] = 0;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while (!q.empty())
    {
        Node cur = q.front();
        q.pop();
        if (cur.x == x2 && cur.y == y2)
        {
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            // 越界
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            // 已访问
            if (dist[nx][ny] != -1)
                continue;

            // 墙不能走
            if (grid[nx][ny] == '*')
                continue;

            // 判断当前格子能否按该方向走出去
            char from = grid[cur.x][cur.y];
            if ((i == 0 || i == 1) && from == '-')
                continue;
            if ((i == 2 || i == 3) && from == '|')
                continue;

            // 判断目标格子能否按该方向走进来
            char to = grid[nx][ny];
            if ((i == 0 || i == 1) && to == '-')
                continue;
            if ((i == 2 || i == 3) && to == '|')
                continue

            dist[nx][ny] = dist[cur.x][cur.y] + 1;
            pre[nx][ny] = cur;//存储这个点从哪里来的
            q.push({nx, ny});
        }
    }

    cout << dist[x2][y2] << endl;
    if (dist[x2][y2] == -1)
    {
        cout << "No path" << endl;
        return 0;
    }

    vector<Node> path;
    Node cur = {x2, y2};
    while (!(cur.x == -1 && cur.y == -1))
    {
        path.push_back(cur);
        cur = pre[cur.x][cur.y];
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < (int)path.size(); i++)
    {
        cout << "(" << path[i].x + 1 << "," << path[i].y + 1 << ")";
        if (i + 1 < (int)path.size()) // 有趣的输出条件
            cout << " -> ";
    }
    cout << endl;
    return 0;
}
