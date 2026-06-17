#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

vector<int> seq;
int pos;

TreeNode* build() {
    if (pos >= (int)seq.size()) return nullptr;
    int v = seq[pos++];
    if (v == -1) return nullptr;
    TreeNode* node = new TreeNode(v);
    node->left  = build();
    node->right = build();
    return node;
}

int treeWidth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int maxWidth = 0;
    while (!q.empty()) {
        int levelSize = (int)q.size();
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
