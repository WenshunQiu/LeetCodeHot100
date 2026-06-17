#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct BTNode {
    int data;
    BTNode *lchild, *rchild;
    BTNode(int x) : data(x), lchild(nullptr), rchild(nullptr) {}
};

// 迭代层序重构二叉树
BTNode* buildTreeFromLevel(vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;
    queue<BTNode*> q;
    BTNode* root = new BTNode(arr[0]);
    q.push(root);
    int idx = 1;
    while (!q.empty() && idx < arr.size()) {
        BTNode* parent = q.front();
        q.pop();
        // 处理左孩子
        if (idx < arr.size() && arr[idx] != -1) {
            parent->lchild = new BTNode(arr[idx]);
            q.push(parent->lchild);
        }
        idx++;
        // 处理右孩子
        if (idx < arr.size() && arr[idx] != -1) {
            parent->rchild = new BTNode(arr[idx]);
            q.push(parent->rchild);
        }
        idx++;
    }
    return root;
}

// 计算二叉树最大宽度
int maxWidth(BTNode* root) {
    if (root == nullptr) return 0;
    queue<pair<BTNode*, unsigned long long>> q;
    q.push({root, 1});
    int maxw = 0;
    while (!q.empty()) {
        int size = q.size();
        unsigned long long left = q.front().second;
        unsigned long long right = left;
        for (int i = 0; i < size; i++) {
            auto cur = q.front();
            q.pop();
            right = cur.second;
            if (cur.first->lchild) {
                q.push({cur.first->lchild, cur.second * 2});
            }
            if (cur.first->rchild) {
                q.push({cur.first->rchild, cur.second * 2 + 1});
            }
        }
        maxw = max(maxw, (int)(right - left + 1));
    }
    return maxw;
}

int main() {
    vector<int> arr = {1, 3, 2, 5, 3, -1, 9};
    BTNode* root = buildTreeFromLevel(arr);
    cout << "最大宽度：" << maxWidth(root) << endl; // 输出4
    return 0;
}
