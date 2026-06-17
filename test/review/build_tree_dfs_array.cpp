#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

/*
 * 输入格式: [1, 2, 4, null, null, 5, null, null, 3]
 *   DFS 前序序列, null 表示空节点
 *
 * 构建的树:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 */

// 把 "[1, 2, null, ...]" 解析成 tokens
vector<string> tokenize(const string &s)
{
    vector<string> tokens;
    string tok;
    for (char c : s)
    {
        if (c == '[' || c == ']' || c == ' ')
            continue;
        if (c == ',')
        {
            if (!tok.empty())
                tokens.push_back(tok);
            tok.clear();
        }
        else
        {
            tok += c;
        }
    }
    if (!tok.empty())
        tokens.push_back(tok);
    return tokens;
}

static vector<string> tokens;
static int pos;

// 递归构建: 读当前位置的 token, null 则返回空, 否则建节点后递归左右
TreeNode *build()
{
    if (pos >= (int)tokens.size())
        return nullptr; // 如果超过就要返回空

    string &t = tokens[pos++];
    if (t == "null")
        return nullptr; // 如果没有节点也要返回空

    TreeNode *node = new TreeNode(stoi(t));
    node->left = build();
    node->right = build(); // 如果有节点，那就要继续构建，因为后面相接的是深度优先遍历，我们也需要dfs来构建树
    return node;
}

TreeNode *buildTree(const string &s)
{
    tokens = tokenize(s);
    pos = 0;
    return build();
}

// 前序遍历验证
void preorder(TreeNode *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// 中序遍历验证
void inorder(TreeNode *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void freeTree(TreeNode *root)
{
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    string s = "[1, 2, 4, null, null, 5, null, null, 3]";
    TreeNode *root = buildTree(s);

    cout << "input:    " << s << endl;
    cout << "preorder: ";
    preorder(root);
    cout << endl;
    cout << "inorder:  ";
    inorder(root);
    cout << endl;

    freeTree(root);
    return 0;
}
