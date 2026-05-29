#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<double> succProb(m);
    for (int i = 0; i < m; i++)
    {
        cin >> succProb[i];
    }

    int start, end;
    cin >> start >> end;

    vector<vector<pair<int, double>>> g(n);
    for (int i = 0; i < m; i++)
    {
        int a = edges[i].first, b = edges[i].second;
        double p = succProb[i];
        g[a].push_back({b, p});
        g[b].push_back({a, p});
    }

    vector<double> best(n, 0.0);
    best[start] = 1.0;

    priority_queue<pair<double, int>> pq; // {prob, node}
    pq.push({1.0, start});

    while (!pq.empty())
    {
        auto [prob, u] = pq.top();
        pq.pop();

        if (prob < best[u])
            continue;
        if (u == end)
            break; // 最大堆，首次到达 end 即最优

        for (auto &[v, w] : g[u])
        {
            double np = prob * w;
            if (np > best[v])
            {
                best[v] = np;
                pq.push({np, v});
            }
        }
    }

    cout << fixed << setprecision(5) << best[end] << "\n";
    return 0;
}
