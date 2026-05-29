#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main()
{
    int n, e;
    cin >> n >> e;
    vector<pair<int, int>> edges(e); // 输入边以及它的概率
    for (int i = 0; i < e; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }
    vector<double> succProb(e);
    for (int i = 0; i < e; i++)
    {
        cin >> succProb[i];
    }
    int start, end;
    cin >> start >> end;
    vector<vector<pair<int, double>>> g(n); // 构建邻接表
    for (int i = 0; i < e; i++)
    {
        int a = edges[i].first, b = edges[i].second;
        double p = succProb[i];
        g[a].push_back({b, p});
        g[b].push_back({a, p});
    }
    vector<double> best(n, 0.0); // 记录从start到某个点的最高概率
    best[start] = 1.0;           // 起点自己的概率为100%
    priority_queue<pair<double, int>> pq;
    pq.push({1.0, start});
    while (!pq.empty())
    {
        auto [prob, nn] = pq.top();
        pq.pop();
        if (prob < best[nn])
        {
            continue;
        }
        if (nn == end)
        {
            break; // 如果下一个是end那就结束了
        }
        for (auto &&[v, w] : g[nn]) // 邻接表更新
        {
            double np = prob * w;
            if (np > best[v])
            {
                best[v] = np;
                pq.push({np, v});
            }
        }
    }
    cout << best[end] << endl;
    return 0;
}