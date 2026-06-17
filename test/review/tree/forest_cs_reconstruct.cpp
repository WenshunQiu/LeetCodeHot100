#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct CSNode {
    int data;
    CSNode *firstchild;
    CSNode *nextsibling;
    CSNode(int x) : data(x), firstchild(nullptr), nextsibling(nullptr) {}
};

// 前序（先根）+ 中序（后根）重构孩子兄弟二叉树
CSNode* build(vector<int>& pre, vector<int>& in, int preL, int preR, int inL, int inR) {
    if (preL > preR) return nullptr;
    int rootVal = pre[preL];
    CSNode* root = new CSNode(rootVal);
    int rootIdx = inL;
    while (rootIdx <= inR && in[rootIdx] != rootVal) rootIdx++;
    int leftLen = rootIdx - inL;
    // 左子树：第一棵子树
    root->firstchild = build(pre, in, preL+1, preL+leftLen, inL, rootIdx-1);
    // 右子树：兄弟树
    root->nextsibling = build(pre, in, preL+leftLen+1, preR, rootIdx+1, inR);
    return root;
}

// 还原森林，返回所有树的根节点
vector<CSNode*> restoreForest(CSNode* root) {
    vector<CSNode*> forest;
    CSNode* cur = root;
    while (cur != nullptr) {
        CSNode* next = cur->nextsibling;
        cur->nextsibling = nullptr; // 断开兄弟链接
        forest.push_back(cur);
        cur = next;
    }
    return forest;
}

// 对单棵树进行层序遍历输出
void levelOrder(CSNode* root, int treeId) {
    cout << "第" << treeId << "棵树的层序：";
    if (root == nullptr) {
        cout << endl;
        return;
    }
    queue<CSNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            CSNode* cur = q.front();
            q.pop();
            cout << cur->data << " ";
            // 遍历所有孩子（第一个孩子开始，沿兄弟链走）
            CSNode* child = cur->firstchild;
            while (child != nullptr) {
                q.push(child);
                child = child->nextsibling;
            }
        }
    }
    cout << endl;
}

int main() {
    // 示例：森林包含2棵树
    // 先根序列：1 2 5 3 4 6
    // 后根序列：5 2 3 1 6 4
    vector<int> pre = {1,2,5,3,4,6};
    vector<int> in = {5,2,3,1,6,4};
    CSNode* root = build(pre, in, 0, pre.size()-1, 0, in.size()-1);
    
    vector<CSNode*> forest = restoreForest(root);
    cout << "森林中树的数量：" << forest.size() << endl;
    for (int i = 0; i < forest.size(); i++) {
        levelOrder(forest[i], i+1);
    }
    return 0;
}
