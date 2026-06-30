#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
struct BTNode
{
    int data;
    BTNode *lchild;
    BTNode *rchild;
    BTNode(int a) : data{a}, rchild{nullptr}, lchild{nullptr} {}
};
// 二叉树的序列化与反序列化
// 这里用string存储变量很聪明

void serialize(BTNode *root, string &str, int isFirst)
{
    if (root == nullptr)
    {
        str.append("null, ");
        return;
    }
    str.append(to_string(root->data) + ", ");
    serialize(root->lchild, str, 0);
    serialize(root->rchild, str, 0);
    if (isFirst)
    { // 是否要去除最后的,
      //  str.pop_back();
      //  str.pop_back();
    }
}
BTNode *_deserialize(const vector<string> &data, int &idx)
{
    if (idx >= data.size())
    {
        return nullptr;
    }

    string cur = data[idx];
    while (!cur.empty() && cur.front() == ' ')
    {
        cur.erase(cur.begin());
    }
    while (!cur.empty() && cur.back() == ' ')
    {
        cur.pop_back();
    }
    if (cur.empty() || cur == "null")
    {
        idx++;
        return nullptr;
    }

    BTNode *root = new BTNode(stoi(cur));
    idx++;
    root->lchild = _deserialize(data, idx);
    root->rchild = _deserialize(data, idx);
    return root;
}
BTNode *deserialize2(const vector<string> &data, int &idx)
{
    if (idx >= data.size())
    {
        return nullptr;
    }
    string cur = data[idx];
    while (!cur.empty() && cur.front() == ' ')
    {
        cur.erase(cur.begin());
    }
    while (!cur.empty() && cur.back() == ' ')
    {
        cur.pop_back();
    }
    if (cur.empty() || cur == "null")
    {
        idx++;
        return nullptr;
    }
    BTNode *root = new BTNode(stoi(cur));
    idx++;
    root->lchild = _deserialize(data, idx);
    root->lchild = _deserialize(data, idx);
    return root; // 构建了左右子树之后就可以返回了，它会一直沿着dfs的方向下降，并沿着路上创建节点，顺序是一样的
}
BTNode *deserialize(const string &data)
{
    vector<string> nodes;
    string token;
    char ch;
    for (auto &&ch : data)
    {
        if (ch != ',')
        {
            token += ch;
        }
        else
        {

            nodes.push_back(token);
            token.erase();
        }
    }
    int idx = 0;
    return _deserialize(nodes, idx);
}

int main()
{
    BTNode *root = new BTNode(1);
    root->lchild = new BTNode(2);
    root->rchild = new BTNode(3);
    BTNode *tmp = root->lchild;
    tmp->lchild = new BTNode(4);
    tmp->rchild = new BTNode(5);
    string a;
    serialize(root, a, 1);
    cout << a << endl;
    BTNode *newRoot = deserialize(a);
    string b;
    serialize(newRoot, b, 1);
    cout << b << endl;
}
