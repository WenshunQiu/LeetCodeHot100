#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 在以 root 为根的子树中，收集距离当前结点 depth 的所有结点
    void collect(TreeNode* root, int depth, vector<int>& ans) {
        if (root == nullptr || depth < 0) return;
        if (depth == 0) {
            ans.push_back(root->val);
            return;
        }
        collect(root->left, depth - 1, ans);
        collect(root->right, depth - 1, ans);
    }

    // 找从 root 到 target 的路径，存到 path 中
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (root == nullptr) return false;
        path.push_back(root);
        if (root == target) return true;
        if (findPath(root->left, target, path) || findPath(root->right, target, path)) {
            return true;
        }
        path.pop_back();
        return false;
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        if (root == nullptr || target == nullptr) return ans;

        vector<TreeNode*> path; // root -> target
        findPath(root, target, path);

        // 1. 先收集 target 子树中距离 k 的结点
        collect(target, k, ans);

        // 2. 再从 target 的父亲开始，依次向上处理
        int m = path.size();
        for (int i = m - 2; i >= 0; --i) {
            TreeNode* ancestor = path[i];
            TreeNode* childOnPath = path[i + 1];
            int upDist = (m - 1 - i);   // ancestor 到 target 的距离

            if (upDist == k) {
                ans.push_back(ancestor->val);
            } else if (upDist < k) {
                int remain = k - upDist - 1;
                if (ancestor->left == childOnPath) {
                    collect(ancestor->right, remain, ans);
                } else {
                    collect(ancestor->left, remain, ans);
                }
            } else {
                break;
            }
        }

        return ans;
    }
};

// 去掉字符串首尾空白
string trim(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l <= r && (s[l] == ' ' || s[l] == '\t' || s[l] == '\n' || s[l] == '\r')) l++;
    while (r >= l && (s[r] == ' ' || s[r] == '\t' || s[r] == '\n' || s[r] == '\r')) r--;
    if (l > r) return "";
    return s.substr(l, r - l + 1);
}

// 解析形如 [1,2,3,#,4] 的字符串
vector<string> parseTreeString(string s) {
    vector<string> tokens;
    s = trim(s);
    if (!s.empty() && s.front() == '[') s.erase(s.begin());
    if (!s.empty() && s.back() == ']') s.pop_back();

    string cur;
    for (char c : s) {
        if (c == ',') {
            tokens.push_back(trim(cur));
            cur.clear();
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) tokens.push_back(trim(cur));
    return tokens;
}

// 根据顺序存储构建二叉树
TreeNode* buildTree(const vector<string>& tokens, vector<TreeNode*>& allNodes) {
    int n = tokens.size();
    allNodes.assign(n, nullptr);

    for (int i = 0; i < n; ++i) {
        if (tokens[i] != "#") {
            allNodes[i] = new TreeNode(stoi(tokens[i]));
        }
    }

    for (int i = 0; i < n; ++i) {
        if (allNodes[i] == nullptr) continue;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n) allNodes[i]->left = allNodes[l];
        if (r < n) allNodes[i]->right = allNodes[r];
    }

    return n > 0 ? allNodes[0] : nullptr;
}

int main() {
    ifstream fin("in.txt");
    if (!fin.is_open()) {
        return 0;
    }

    string line1, line2, line3;
    getline(fin, line1);
    getline(fin, line2);
    getline(fin, line3);
    fin.close();

    vector<string> tokens = parseTreeString(line1);

    vector<TreeNode*> allNodes;
    TreeNode* root = buildTree(tokens, allNodes);

    int targetVal = stoi(trim(line2));
    int k = stoi(trim(line3));

    TreeNode* target = nullptr;
    for (TreeNode* node : allNodes) {
        if (node != nullptr && node->val == targetVal) {
            target = node;
            break;
        }
    }

    Solution sol;
    vector<int> ans = sol.distanceK(root, target, k);

    cout << "[";
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i > 0) cout << ",";
        cout << ans[i];
    }
    cout << "]" << endl;

    return 0;
}