#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>
using namespace std; // 这个后序遍历解题需要理解一下

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 去掉字符串中的空格
string removeSpaces(string s)
{
    string res;
    for (char c : s)
    {
        if (c != ' ')
            res += c;
    }
    return res;
}

// 解析 root = [1,2,3,null,null,15,7]
vector<string> parseInput(string line)
{
    line = removeSpaces(line);

    int l = line.find('[');
    int r = line.find(']');

    string content = line.substr(l + 1, r - l - 1);

    vector<string> vals;
    string cur;

    for (char c : content)
    {
        if (c == ',')
        {
            vals.push_back(cur);
            cur.clear();
        }
        else
        {
            cur += c;
        }
    }

    if (!cur.empty())
    {
        vals.push_back(cur);
    }

    return vals;
}

// 根据层序数组建树
TreeNode *buildTree(vector<string> &vals)
{
    if (vals.empty() || vals[0] == "null")
        return nullptr;

    TreeNode *root = new TreeNode(stoi(vals[0]));
    queue<TreeNode *> q; // 队列建树
    q.push(root);

    int i = 1;

    while (!q.empty() && i < vals.size())
    {
        TreeNode *cur = q.front();
        q.pop();

        if (i < vals.size() && vals[i] != "null")
        {
            cur->left = new TreeNode(stoi(vals[i]));
            q.push(cur->left);
        }
        i++;

        if (i < vals.size() && vals[i] != "null")
        {
            cur->right = new TreeNode(stoi(vals[i]));
            q.push(cur->right);
        }
        i++;
    }

    return root;
}

class Solution
{
public:
    int ans = INT_MIN;

    int dfs(TreeNode *root)
    {
        if (!root)
            return 0;

        int leftGain = max(0, dfs(root->left));   // 走左边，得到以左边节点为根的子树中，最大的贡献
        int rightGain = max(0, dfs(root->right)); // 走右边，得到以右边节点为根的子树中，最大的贡献

        int curPathSum = root->val + leftGain + rightGain; // 作为路径的最高点，它的路径和为当前节点的值加上左右子节点的最大路径和

        ans = max(ans, curPathSum); // 一直取最大

        return root->val + max(leftGain, rightGain); // 只能走一条路，返回其中的最大值，也保证了前面走子树的过程中，顶点是左/右子树。
    }

    int maxPathSum(TreeNode *root)
    {
        dfs(root);
        return ans;
    }
};

int main()
{
    string line;
    getline(cin, line);

    vector<string> vals = parseInput(line);

    TreeNode *root = buildTree(vals);

    Solution sol;
    cout << sol.maxPathSum(root) << endl;

    return 0;
}