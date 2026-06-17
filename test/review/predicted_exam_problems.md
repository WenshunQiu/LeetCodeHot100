# 期末押题 — 两道算法题

提纲中两条最明确的线索：

1. "**建议仔细研究用图解决迷宫问题**" → 押题 1
2. "**建议仔细研究教材中关于求二叉树的宽度的示例代码**" → 押题 2

其余要点（递归/迭代、栈/队列、非标准概念）都是围绕这两题展开的。

---

## 押题 1：迷宫最短路径（BFS + 队列）

### 题目

给定一个 m×n 的迷宫矩阵，`0` 表示通路，`1` 表示墙壁。入口在左上角 `(0,0)`，出口在右下角 `(m-1,n-1)`。
每次只能向上下左右移动一格。求从入口到出口的**最短路径长度**（经过的格子数，含起点和终点）。若不可达输出 `-1`。

### 输入格式

```
m n
m 行，每行 n 个整数（0 或 1）
```

### 样例输入

```
5 5
0 0 1 0 0
1 0 1 0 1
0 0 0 0 0
0 1 1 1 0
0 0 0 0 0
```

### 样例输出

```
9
```

路径：(0,0)→(0,1)→(1,1)→(2,1)→(2,2)→(2,3)→(2,4)→(3,4)→(4,4)，共 9 格。

### 完整代码

```cpp
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

    // 起点或终点被封死
    if (g[0][0] == 1 || g[m-1][n-1] == 1) {
        cout << -1 << endl;
        return 0;
    }

    // BFS
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    queue<Node> q;
    q.push({0, 0, 1});       // 起点算第 1 格
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

    cout << -1 << endl;      // 不可达
    return 0;
}
```

### 考前速记

**核心模板（BFS 求最短路径）：**

```
queue<Node> q;
q.push(起点); visited[起点] = true;
while (!q.empty()) {
    取出队首;
    if (是终点) 输出距离;
    for (四个方向) {
        if (合法 && 未访问) { 标记访问; 入队; }
    }
}
输出 -1;  // 不可达
```

**要点：**
- 迷宫 = 无权图，BFS 天然求最短路径
- `visited` 数组防重复访问，必须在入队时标记（不是出队时）
- `dist` 从 1 开始（含起点），找到终点即为答案
- 若要输出具体路径：额外开一个 `parent[][]` 数组记录每个格子的前驱，到达终点后回溯

---

## 押题 2：从先序 DFS 序列重建二叉树 → 求宽度

### 题目

给定一棵二叉树的**先序遍历序列**（用 `-1` 表示空节点），根据该序列重建二叉树。

定义**二叉树的宽度**：层序遍历中，节点数最多的那一层的节点个数。

输出重建后二叉树的宽度。

### 输入格式

一行整数，空格分隔，`-1` 表示空节点。

### 样例输入

```
1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
```

对应二叉树：

```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

### 样例输出

```
4
```

（第 3 层有 4 个节点：4, 5, 6, 7）

### 完整代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

vector<int> seq;  // 先序序列
int pos;          // 当前读取位置

// 递归建树：读一个值，-1 则空，否则建节点后递归左右子树
TreeNode* build() {
    if (pos >= (int)seq.size()) return nullptr;
    int v = seq[pos++];
    if (v == -1) return nullptr;
    TreeNode* node = new TreeNode(v);
    node->left  = build();
    node->right = build();
    return node;
}

// 层序遍历求宽度
int treeWidth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int maxWidth = 0;
    while (!q.empty()) {
        int levelSize = (int)q.size();  // 当前层的节点数
        maxWidth = max(maxWidth, levelSize);
        for (int i = 0; i < levelSize; i++) {
            TreeNode* t = q.front(); q.pop();
            if (t->left)  q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
    return maxWidth;
}

void freeTree(TreeNode* t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

int main() {
    int x;
    while (cin >> x) seq.push_back(x);
    pos = 0;
    TreeNode* root = build();
    cout << treeWidth(root) << endl;
    freeTree(root);
    return 0;
}
```

### 考前速记

**核心模板 1 — 递归建树：**

```
TreeNode* build() {
    读一个值 v;
    if (v == -1) return nullptr;
    建节点 node(v);
    node->left  = build();   // 递归建左子树
    node->right = build();   // 递归建右子树
    return node;
}
```

**核心模板 2 — BFS 求宽度：**

```
queue<TreeNode*> q;  q.push(root);
while (!q 不空) {
    levelSize = q.size();       // 当前层节点数
    maxWidth = max(maxWidth, levelSize);
    for (i = 0; i < levelSize; i++) {
        取队首 t; 出队;
        if (t->left)  入队;
        if (t->right) 入队;
    }
}
```

**要点：**
- 先序序列建树 = 递归读序列：根 → 左子树 → 右子树
- 全局变量 `seq` 和 `pos` 简化参数传递（考场上省时间）
- 求宽度的关键：`q.size()` 在每层循环开始时取一次，就是该层的节点数
- 这道题是**递归建树 + BFS 层序遍历**的组合，两个模板必须都能默写

---

## 可能的变体

**迷宫变体：**
- 要求输出具体路径（用 `parent[][]` 数组记录前驱，到达终点后回溯）
- 起点/终点由输入指定（不是固定的左上/右下）
- 允许对角线移动（8 方向，偏移量数组多 4 个）
- 用 DFS 判断"是否存在路径"（不要求最短，只判断可达性）

**二叉树变体：**
- 非标准概念可能换成**带权路径长度 WPL** = 所有叶子的 (值 × 深度) 之和
- 或**树的直径** = 任意两节点间的最长路径
- 或要求输出**层序遍历序列本身**（不只是宽度）
- 输入格式可能用**括号表示法** `(A(B(C)(D))(E))` 或 **DFS 数组** `[1,2,4,null,null,5,null,null,3]`
- 可能要求用**非递归方式**遍历（用 `std::stack` 模拟递归）

---

## 考点覆盖总结

| 考纲要点 | 押题 1（迷宫） | 押题 2（二叉树宽度） |
|---------|:---:|:---:|
| 图的构建（输入→图结构） | ✓ | |
| 图的存储结构 | ✓（二维数组隐式存储） | |
| 图的遍历（DFS/BFS） | ✓（BFS） | |
| 路径长度计算 | ✓（最短路径） | |
| 树的重构（DFS序列→树） | | ✓ |
| 树的遍历（前/中/后序） | | ✓（层序遍历） |
| 树中的路径/宽度 | | ✓（非标准概念） |
| 递归构造算法 | | ✓（递归建树） |
| 迭代 + 队列/栈 | ✓（队列 BFS） | ✓（队列层序） |
| std::queue / std::stack | ✓ (queue) | ✓ (queue) |

两题合在一起，完美覆盖全部 5 条考纲要点。
