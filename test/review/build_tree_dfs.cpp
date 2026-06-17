#include <iostream>
#include <string>
#include <cassert>
using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

/*
 * 格式: 每个节点用括号包裹 (val [left] [right])
 *   (A)           -> 叶子 A
 *   (A(B))        -> A 只有左孩子 B
 *   (A(B)(C))     -> A 左 B 右 C
 *   (A()(B))      -> A 无左, 右孩子 B
 *   ()            -> 空节点
 *
 * 例: (A(B(C)(D))(E))
 *        A
 *       / \
 *      B   E
 *     / \
 *    C   D
 */

static string g;
static int pos;

TreeNode* parse() {
    assert(g[pos] == '(');
    pos++;  // 消费 '('

    // 空节点 ()
    if (g[pos] == ')') {
        pos++;
        return nullptr;
    }

    // 读取节点值
    char val = g[pos++];
    TreeNode* node = new TreeNode(val);

    // 可选左子树
    if (g[pos] == '(')
        node->left = parse();

    // 可选右子树
    if (g[pos] == '(')
        node->right = parse();

    assert(g[pos] == ')');
    pos++;  // 消费 ')'
    return node;
}

TreeNode* buildTree(const string& s) {
    g = s;
    pos = 0;
    TreeNode* root = parse();
    assert(pos == (int)s.size());
    return root;
}

// 前序遍历验证
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

// 中序遍历验证
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    string s = "(A(B(C)(D))(E))";
    TreeNode* root = buildTree(s);

    cout << "input:   " << s << endl;
    cout << "preorder: ";
    preorder(root);
    cout << endl;
    cout << "inorder:  ";
    inorder(root);
    cout << endl;

    freeTree(root);
    return 0;
}
