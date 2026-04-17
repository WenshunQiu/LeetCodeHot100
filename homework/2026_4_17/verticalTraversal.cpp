#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 解析输入字符串
vector<string> parseInput(const string &line)
{
    vector<string> result;

    size_t bracketStart = line.find('[');
    size_t bracketEnd = line.find(']');

    if (bracketStart == string::npos || bracketEnd == string::npos)
    {
        return result;
    }

    string content = line.substr(bracketStart + 1, bracketEnd - bracketStart - 1);
    stringstream ss(content);
    string token;
    while (getline(ss, token, ','))
    {
        size_t start = token.find_first_not_of(" ");
        size_t end = token.find_last_not_of(" ");
        if (start != string::npos)
        {
            result.push_back(token.substr(start, end - start + 1));
        }
        else
        {
            result.push_back(token);
        }
    }
    return result;
}

// 从层序序列构建二叉树
TreeNode *buildTree(const vector<string> &nodes)
{
    if (nodes.empty() || nodes[0] == "null" || nodes[0].empty())
    {
        return nullptr;
    }

    TreeNode *root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode *> q;
    q.push(root);
    int index = 1;

    while (!q.empty() && index < nodes.size())
    {
        TreeNode *node = q.front();
        q.pop();

        if (index < nodes.size() && nodes[index] != "null" && !nodes[index].empty())
        {
            node->left = new TreeNode(stoi(nodes[index]));
            q.push(node->left);
        }
        index++;

        if (index < nodes.size() && nodes[index] != "null" && !nodes[index].empty())
        {
            node->right = new TreeNode(stoi(nodes[index]));
            q.push(node->right);
        }
        index++;
    }

    return root;
}

// DFS遍历记录每个节点的位置和值
void dfs(TreeNode *node, int row, int col, map<int, vector<pair<int, int>>> &colMap)
{
    if (node == nullptr)
    {
        return;
    }

    colMap[col].push_back({row, node->val});
    dfs(node->left, row + 1, col - 1, colMap);
    dfs(node->right, row + 1, col + 1, colMap);
}

// 垂序遍历
vector<vector<int>> verticalTraversal(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == nullptr)
    {
        return result;
    }

    map<int, vector<pair<int, int>>> colMap;
    dfs(root, 0, 0, colMap);

    for (auto &[col, nodes] : colMap)
    {
        sort(nodes.begin(), nodes.end());
        vector<int> colResult;
        for (auto &[row, val] : nodes)
        {
            colResult.push_back(val);
        }
        result.push_back(colResult);
    }

    return result;
}

int main()
{
    string line;
    getline(cin, line);

    vector<string> nodes = parseInput(line);
    TreeNode *root = buildTree(nodes);

    vector<vector<int>> result = verticalTraversal(root);

    if (result.empty())
    {
        return 0;
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); i++)
    {
        if (i > 0)
            cout << ",";
        cout << "[";
        for (size_t j = 0; j < result[i].size(); j++)
        {
            if (j > 0)
                cout << ",";
            cout << result[i][j];
        }
        cout << "]";
    }
    cout << "]" << endl;

    return 0;
}
