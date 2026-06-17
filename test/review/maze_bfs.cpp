#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node { int r, c, dist; };

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> g(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    if (g[0][0] == 1 || g[m-1][n-1] == 1) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<bool>> vis(m, vector<bool>(n, false));
    queue<Node> q;
    q.push({0, 0, 1});
    vis[0][0] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        if (cur.r == m-1 && cur.c == n-1) {
            cout << cur.dist << endl;
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i], nc = cur.c + dc[i];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n
                && g[nr][nc] == 0 && !vis[nr][nc]) {
                vis[nr][nc] = true;
                q.push({nr, nc, cur.dist + 1});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
