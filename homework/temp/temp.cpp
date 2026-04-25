#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
int main()
{
    string s;
    getline(cin, s);
    int pos = s.find(" = ");
    if (pos == string::npos)
    {
        return 0;
    }

    string a = s.substr(pos + 3);
    cout << a << endl;
}

string serialize_BFS(TreeNode *root)
{
    if (!root)
        return "[]";

    vector<string> res;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
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

    // 去掉末尾多余的 null
    while (!res.empty() && res.back() == "null")
    {
        res.pop_back();
    }

    // 拼接字符串
    string ans = "[";
    for (int i = 0; i < res.size(); i++)
    {
        if (i > 0)
            ans += ",";
        ans += res[i];
    }
    ans += "]";

    return ans;
}