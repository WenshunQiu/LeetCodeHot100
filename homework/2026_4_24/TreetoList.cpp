#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
struct Node
{
    string val;
    int num;
    Node *left, *right;
    Node(int x) : num(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
    Node *pre = nullptr;
    Node *head = nullptr;
    void inorder(Node *cur)//这里是中序遍历构建链表
    {
        if (!cur)
            return;
        inorder(cur->left);
        if (!pre)
        {
            head = cur;
        }
        else
        {
            pre->right = cur;
            cur->left = pre;
        }
        pre = cur;
        inorder(cur->right);
    }

public:
    Node *treeToDoublyList(Node *root)
    {
        if (!root)
        {
            return nullptr;
        }
        inorder(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
};
Node *buildTree(const vector<string> &nodes) // 创建树，使用队列，可以通用
{
    if (nodes.empty() || nodes[0] == "#")
    {
        return nullptr;
    }
    Node *root = new Node(stoi(nodes[0]));
    queue<Node *> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < nodes.size())
    {
        Node *cur = q.front();
        q.pop();
        if (i < nodes.size() && nodes[i] != "#")
        {
            cur->left = new Node(stoi(nodes[i]));
            q.push(cur->left);
        }
        i++;
        if (i < nodes.size() && nodes[i] != "#")
        {
            cur->right = new Node(stoi(nodes[i]));
            q.push(cur->right);
        }
        i++;
    }
    return root;
}
int main()
{
    string line, x;
    getline(cin, line);
    stringstream ss(line);
    vector<string> nodes;
    while (ss >> x)
    {
        nodes.push_back(x);
    }
    Node *root = buildTree(nodes);
    Solution s;
    Node *head = s.treeToDoublyList(root);
    if (!head)
        return 0;
    Node *cur = head;
    do
    {
        cout << cur->num << " ";
        cur = cur->right;
        if (cur != head)
            cout << "<-> ";
    } while (cur != head);
    return 0;
}
