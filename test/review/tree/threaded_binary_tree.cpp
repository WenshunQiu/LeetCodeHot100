#include <iostream>
#include <vector>
using namespace std;

struct ThreadNode {
    int data;
    ThreadNode *lchild, *rchild;
    bool ltag, rtag;
    ThreadNode(int x) : data(x), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0) {}
};

// 前序+中序重构二叉树骨架
ThreadNode* build(vector<int>& preorder, vector<int>& inorder, int preL, int preR, int inL, int inR) {
    if (preL > preR) return nullptr;
    int rootVal = preorder[preL];
    ThreadNode* root = new ThreadNode(rootVal);
    int rootIdx = inL;
    while (rootIdx <= inR && inorder[rootIdx] != rootVal) rootIdx++;
    int leftLen = rootIdx - inL;
    root->lchild = build(preorder, inorder, preL+1, preL+leftLen, inL, rootIdx-1);
    root->rchild = build(preorder, inorder, preL+leftLen+1, preR, rootIdx+1, inR);
    return root;
}

ThreadNode* buildTree(vector<int>& pre, vector<int>& in) {
    return build(pre, in, 0, pre.size()-1, 0, in.size()-1);
}

// 全局前驱指针（使用preNode避免与std::prev冲突）
ThreadNode* preNode = nullptr;

// 中序线索化
void inThread(ThreadNode* root) {
    if (root == nullptr) return;
    inThread(root->lchild); // 左子树线索化
    
    // 处理当前节点前驱
    if (root->lchild == nullptr) {
        root->ltag = 1;
        root->lchild = preNode;
    }
    // 处理前驱节点的后继
    if (preNode != nullptr && preNode->rchild == nullptr) {
        preNode->rtag = 1;
        preNode->rchild = root;
    }
    preNode = root; // 更新前驱
    
    inThread(root->rchild); // 右子树线索化
}

// 基于线索的无栈中序遍历
void threadInOrder(ThreadNode* root) {
    ThreadNode* cur = root;
    // 先找到最左节点
    while (cur != nullptr && cur->ltag == 0) {
        cur = cur->lchild;
    }
    while (cur != nullptr) {
        cout << cur->data << " ";
        // 右指针是线索，直接走后继
        if (cur->rtag == 1) {
            cur = cur->rchild;
        } else {
            // 右子树存在，找右子树最左节点
            cur = cur->rchild;
            while (cur != nullptr && cur->ltag == 0) {
                cur = cur->lchild;
            }
        }
    }
    cout << endl;
}

int main() {
    vector<int> preorder = {1,3,5,3,2,9};
    vector<int> inorder = {5,3,3,1,2,9};
    ThreadNode* root = buildTree(preorder, inorder);
    preNode = nullptr; // 重置全局前驱
    inThread(root);
    threadInOrder(root); // 输出 5 3 3 1 2 9
    return 0;
}
