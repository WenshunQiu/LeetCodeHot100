#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    unordered_map<int, int> pos;

    TreeNode *build(
        vector<int> &preorder,
        int preL,
        int preR,
        vector<int> &inorder,
        int inL,
        int inR)
    { // build(preorder, 0, n - 1, inorder, 0, n - 1);
        if (preL > preR || inL > inR)
        {
            return nullptr;
        }

        int rootVal = preorder[preL];
        TreeNode *root = new TreeNode(rootVal);

        int rootIndex = pos[rootVal];   //  先序遍历的值作为索引在中序遍历中可以将根节点的左右子树区分开
        int leftSize = rootIndex - inL; // 左子树的大小

        root->left = build(
            preorder,        // 不变
            preL + 1,        // 左子树的先序遍历起始索引
            preL + leftSize, // 左子树的先序遍历结束索引
            inorder,         // 不变
            inL,             // 左子树的中序遍历起始索引
            rootIndex - 1);  // 左子树的中序遍历末尾

        root->right = build(
            preorder,            // 不变
            preL + leftSize + 1, // 右子树的先序遍历起始索引（除去左边就是右边了）
            preR,                // 右子树的先序遍历结束索引
            inorder,             // 不变
            rootIndex + 1,       // 右子树中序遍历起始索引
            inR);                // 右子树中序遍历结束索引

        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = inorder.size();

        for (int i = 0; i < n; i++)
        {
            pos[inorder[i]] = i;
        }

        return build(preorder, 0, n - 1, inorder, 0, n - 1);
    }
};

void printLevelOrder(TreeNode *root)
{
    if (!root)
    {
        cout << "[]" << endl;
        return;
    }

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

    while (!res.empty() && res.back() == "null")
    {
        res.pop_back();
    }

    cout << "[";
    for (int i = 0; i < res.size(); i++)
    {
        if (i > 0)
            cout << ",";
        cout << res[i];
    }
    cout << "]" << endl;
}

int main()
{
    int n;
    cin >> n;

    vector<int> preorder(n), inorder(n);

    for (int i = 0; i < n; i++)
    {
        cin >> preorder[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
    }

    Solution sol;
    TreeNode *root = sol.buildTree(preorder, inorder);

    printLevelOrder(root);

    return 0;
}