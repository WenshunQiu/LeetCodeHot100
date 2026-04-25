#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}; // 这是树的结构体.

string removeSpace(string s)
{
    string res = "";
    for (auto &&c : s)
    {
        if (c != ' ')
        {
            res += c;
        }
    }
    return res;
}

vector<string> parseInput(string line)
{
    line = removeSpace(line);
    int l = line.find('[');
    int r = line.find(']');
    string content = line.substr(l + 1, r - l - 1);
    vector<string> vals;
    string cur;
    for (auto &&c : content)
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
    } // 把每一个部分单独成串，拿出来
    if (!cur.empty())
    {
        vals.push_back(cur);
    } // 处理最后一个串
    return vals;
}

TreeNode *buildTree(vector<string> &vals)
{
    if (vals.empty() || vals[0] == "null")
    {
        return nullptr;
    }
    TreeNode *root = new TreeNode(stoi(vals[0])); // 根节点
    queue<TreeNode *> q;                          // 使用BFS
    q.push(root);
    int i = 1;                            // 处理到第几个数据的索引
    while (!q.empty() && i < vals.size()) // 对每个头节点都这样处理
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

string serialize_BFS(TreeNode *root)
{
    if (!root)
    {
        return "[]";
    }
    vector<string> res;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) // BFS遍历并把各个值输入到res中
    {
        TreeNode *cur = q.front();
        q.pop();
        if (cur)
        {
            res.push_back(to_string(cur->val));
            q.push(cur->left);
            q.push(cur->right);
        }
        else
        {
            res.push_back("null");
        }
    }

    // 去除末尾多余的null
    while (!res.empty() && res.back() == "null")
    {
        res.pop_back();
    }

    // 拼接字符串
    string ans = "[";
    for (auto &s : res)
    {
        ans += s;
        ans += ',';
    }
    ans += "]";
    return ans;
}

