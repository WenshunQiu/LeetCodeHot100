# 图的连通分量 - 代码集合

本目录包含从 `test/review/graph/graph_components.md` 中提取的4道图的连通分量相关题目的完整代码实现。

## 文件列表

### 1. connected_components_count.cpp

**题目**：连通分量计数与最大分量
**功能**：给定无向图，计算连通分量的个数和最大连通分量的节点数
**输入样例**：

```
7 5
1 2
2 3
4 5
6 7
7 1
```

**输出样例**：`2 5`（2个连通分量，最大的有5个节点）

---

### 2. connectivity_query.cpp

**题目**：连通性查询（多次询问）
**功能**：预处理后支持 O(1) 时间查询任意两个节点是否连通
**输入样例**：

```
7 5
1 2
2 3
4 5
6 7
7 1
4
1 4
1 6
2 7
4 5
```

**输出样例**：

```
NO
YES
YES
YES
```

---

### 3. island_count.cpp

**题目**：岛屿计数（网格 BFS）
**功能**：在二维网格中统计岛屿（连通的陆地）数量
**输入样例**：

```
4 5
1 1 0 0 0
0 1 0 1 1
0 0 0 1 0
1 0 1 0 0
```

**输出样例**：`4`

---

### 4. min_edges_to_connect.cpp

**题目**：使图连通的最少边数
**功能**：计算最少需要添加几条边才能使整个图连通

本质就是将每一块连接起来，所以最后输出的就是联通块的数目-1
**输入样例**：

```
7 5
1 2
2 3
4 5
6 7
7 1
```

**输出样例**：`1`（2个连通分量，只需1条边）

---

## 共同解题模式

所有题目都基于相同的 BFS 模板：

```cpp
// 1. 邻接表构建
vector<vector<int>> adj(n + 1);
for (每条边 u-v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// 2. BFS 遍历连通分量
vector<bool> vis(n + 1, false);
for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    // i 是新分量的起点
    queue<int> q;
    q.push(i);
    vis[i] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
```

## 编译和运行

```bash
# 编译
g++ filename.cpp -o filename.exe

# 运行
./filename.exe

# 或直接使用管道输入测试
echo "输入数据" | ./filename.exe
```

## 核心知识点

- **图的表示**：邻接表存储
- **BFS 遍历**：队列实现广度优先搜索
- **连通分量**：每次从未访问节点出发的 BFS 找到一个连通分量
- **变体技巧**：
  - 计数：外层循环 `compCount++`，BFS 内部 `size++`
  - 标记：用 `comp[]` 数组代替 `vis[]` 存储分量编号
  - 网格：将邻接表换成二维网格 + 四方向偏移量
  - 最少加边：`compCount - 1`

## 来源

这些代码提取自：`test/review/graph/graph_components.md`
