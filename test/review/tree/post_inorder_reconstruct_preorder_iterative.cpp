#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct BTNode {
    int data;
    BTNode *lchild, *rchild;
    BTNode(int x) : data(x), lchild(nullptr), rchild(nullptr) {}
};

// 原地下标递归重构
BTNode* build(vector<int>& post, vector<int>& in, int postL, int postR, int inL, int inR) {
    if (postL > postR || inL > inR) return nullptr;
    int rootVal = post[postR]; // 后序末尾为根
    BTNode* root = new BTNode(rootVal);
    // 在中序中找根的位置
    int rootIdx = inL;
    while (rootIdx <= inR && in[rootIdx] != rootVal) {
        rootIdx++;
    }
    int leftLen = rootIdx - inL; // 左子树长度
    // 递归构建左右子树
    root->lchild = build(post, in, postL, postL + leftLen - 1, inL, rootIdx - 1);
    root->rchild = build(post, in, postL + leftLen, postR - 1, rootIdx + 1, inR);
    return root;
}

BTNode* buildTree(vector<int>& postorder, vector<int>& inorder) {
    return build(postorder, inorder, 0, postorder.size()-1, 0, inorder.size()-1);
}

// 迭代前序遍历
void preOrderIter(BTNode* root) {
    if (root == nullptr) return;
    stack<BTNode*> st;
    st.push(root);
    while (!st.empty()) {
        BTNode* cur = st.top();
        st.pop();
        cout << cur->data << " ";
        // 先压右，再压左，保证左先出栈
        if (cur->rchild) st.push(cur->rchild);
        if (cur->lchild) st.push(cur->lchild);
    }
    cout << endl;
}

int main() {
    vector<int> post = {5,3,3,9,2,1};
    vector<int> in = {5,3,3,1,2,9};
    BTNode* root = buildTree(post, in);
    preOrderIter(root); // 输出 1 3 5 3 2 9
    return 0;
}
