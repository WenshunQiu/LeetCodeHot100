#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    vector<Node*> children;
    Node(int x) : data(x) {}
};

// 递归重构多叉树，idx用引用传递全局推进
Node* buildTree(vector<int>& arr, int& idx) {
    if (idx >= arr.size() || arr[idx] == -1) {
        idx++;
        return nullptr;
    }
    Node* root = new Node(arr[idx]);
    idx++;
    // 循环构建所有子节点，直到遇到-1回溯
    while (idx < arr.size() && arr[idx] != -1) {
        Node* child = buildTree(arr, idx);
        if (child != nullptr) {
            root->children.push_back(child);
        }
    }
    idx++; // 跳过当前节点的回溯标记-1
    return root;
}

// 层序遍历输出每层节点数
void levelOrderCount(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    int floor = 1;
    while (!q.empty()) {
        int size = q.size();
        cout << "第" << floor << "层节点数：" << size << endl;
        for (int i = 0; i < size; i++) {
            Node* cur = q.front();
            q.pop();
            // 所有子节点入队
            for (Node* child : cur->children) {
                q.push(child);
            }
        }
        floor++;
    }
}

int main() {
    vector<int> arr = {1, 2, 5, -1, -1, 3, -1, 4, -1, -1};
    int idx = 0;
    Node* root = buildTree(arr, idx);
    levelOrderCount(root);
    return 0;
}
