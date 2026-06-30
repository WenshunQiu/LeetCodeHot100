#include <vector>
#include <iostream>
#include "textbook/graph/graph.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

struct Island
{
    double x, y, people;
};
// 计算两个岛的几何距离
double getDist(const Island &a, const Island &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 这个是用来计算路径的最大边长，顺便把光缆也计算了
void dfsTime(int u, int parent, double curTime,
             const vector<vector<pair<int, double>>> &tree,
             const vector<Island> &islands,
             double &weightedSum)
{
    weightedSum += curTime * islands[u].people;
    for (auto &&edge : tree[u])
    {
        int v = edge.first;
        double w = edge.second;
        if (v == parent)
        {
            continue;
        }
        // 这里所有光缆同时铺设
        //  所以接入时间取路径上的最大边长，而不是边权和
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
    // const double INF = 1e100;
    // 这里是prim算法需要使用的三个数组
    vector<double> minDist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> used(n, false);
    // 这个是prim算法的起点，也是主岛
    minDist[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        double best = INF;
        // 选择当前距离生成树最近的点
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && minDist[j] < best)
            {
                best = minDist[j];
                u = j;
            }
        }
        used[u] = true;
        for (int v = 0; v < n; v++)
        {
            if (used[v] || u == v)
            {
                continue;
            }
            double d = getDist(islands[u], islands[v]);
            if (d < minDist[v])
            {
                minDist[v] = d;
                parent[v] = u;
            }
        }
    }
    vector<vector<pair<int, double>>> tree(n);
    for (int i = 1; i < n; i++)
    {
        double d = getDist(islands[i], islands[parent[i]]);
        tree[i].push_back({parent[i], d});
        tree[parent[i]].push_back({i, d});
    }
    double weightedSum = 0;
    dfsTime(0, -1, 0, tree, islands, weightedSum);
    printf("%.2f\n", weightedSum / totalPeople);
    return 0;
}