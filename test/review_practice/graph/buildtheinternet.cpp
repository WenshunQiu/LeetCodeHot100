#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

// 记录每个岛屿的信息
// x, y 表示坐标
// people 表示居民人数
struct Island
{
    double x;
    double y;
    double people;
};

// 计算两个岛屿之间的几何距离
double getDist(const Island &a, const Island &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 在最小生成树上 DFS，统计 sum(mi * ti)
// u: 当前节点
// parent: 父节点，防止走回头路
// curTime: 从主岛到当前岛路径上的最大边长
// 这个dfs递归有没有很像
void dfsTime(int u, int parent, double curTime,
             const vector<vector<pair<int, double>>> &tree,
             const vector<Island> &islands,
             double &weightedSum)
{
    weightedSum += curTime * islands[u].people;

    for (const auto &edge : tree[u])
    {
        int v = edge.first;
        double w = edge.second;
        if (v == parent)
            continue;

        // 所有光缆同时铺设，真就所有的光缆一起铺设而不是从头铺到尾啊
        // 所以接入时间取路径上的最大边长，而不是边权和
        // 由于dfs搜索的特性，我们只需要关注一条路就可以了
        dfsTime(v, u, max(curTime, w), tree, islands, weightedSum);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<Island> islands(n);
    double totalPeople = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> islands[i].x >> islands[i].y >> islands[i].people;
        totalPeople += islands[i].people;
    }

    const double INF = 1e100;

    // Prim 算法需要的三个数组
    vector<double> minDist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> used(n, false);

    // 0 号点是主岛，也是 Prim 的起点
    minDist[0] = 0;

    // 朴素 Prim，时间复杂度 O(n^2)
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        double best = INF;

        // 选出当前距离生成树最近的点
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && minDist[j] < best)
            {
                best = minDist[j];
                u = j;
            }
        }

        used[u] = true;

        // 用新加入的点更新其他点到生成树的最短距离
        for (int v = 0; v < n; v++)
        {
            if (used[v] || u == v)
                continue;

            double d = getDist(islands[u], islands[v]);
            if (d < minDist[v])
            {
                minDist[v] = d;
                parent[v] = u;
            }
        }
    }
    // 使用距离来建立最小树

    // 根据 parent 数组建出最小生成树
    vector<vector<pair<int, double>>> tree(n);
    for (int i = 1; i < n; i++)
    {
        double d = getDist(islands[i], islands[parent[i]]);
        tree[i].push_back({parent[i], d});
        tree[parent[i]].push_back({i, d});
    }

    double weightedSum = 0;
    dfsTime(0, -1, 0, tree, islands, weightedSum);

    // 不用 iomanip，改用 printf 保留两位小数
    printf("%.2f\n", weightedSum / totalPeople);
    return 0;
}
