#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // BFS 标记每个节点所属的连通分量编号
    vector<int> comp(n + 1, -1);
    int compId = 0;
    for (int i = 1; i <= n; i++) {
        if (comp[i] != -1) continue;
        queue<int> q;
        q.push(i);
        comp[i] = compId;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = compId;
                    q.push(v);
                }
            }
        }
        compId++;
    }

    // 查询
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (comp[a] == comp[b] ? "YES" : "NO") << endl;
    }
    return 0;
}
