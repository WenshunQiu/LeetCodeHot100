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
    int ans = 0;

    vector<int> dfs(TreeNode *root)
    {
        //                  min     max     sum
        vector<int> rst = {INT_MAX, INT_MIN, 0}; // 默认这个满足树，min 值最大，max 值最小，sum 值最小
        if (!root)
            return rst;

        auto left = dfs(root->left);   // 走左边，得到以左边节点为根的子树中，最大的贡献
        auto right = dfs(root->right); // 走右边，得到以右边节点为根的子树中，最大的贡献
        if (left[1] < root->val && root->val < right[0])
        {
            rst[0] = min(left[0], root->val);
            rst[1] = max(right[1], root->val);
            // 加max和min是为了从排除无子树的节点的干扰
            rst[2] = left[2] + right[2] + root->val;
            ans = max(ans, rst[2]);
        }
        else
            return {INT_MIN, INT_MAX, 0};
        return rst;
    }

    int maxSumBST(TreeNode *root)
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
    cout << sol.maxSumBST(root) << endl;

    return 0;
}