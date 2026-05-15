#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct Node
{
    string val;
    int num;
    Node *left, *right;
    Node(int x) : num(x), left(nullptr), right(nullptr) {}
};

int levelnum(Node *root, int n)
{
    if (root == nullptr)
    {
        return 0;
    }
    if (n < 1)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }

    queue<Node *> q;
    q.push(root);
    int depth = 1;

    while (!q.empty())
    {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++)
        {
            Node *tmp = q.front();
            q.pop();

            if (tmp->left != nullptr)
            {
                q.push(tmp->left);
            }
            if (tmp->right != nullptr)
            {
                q.push(tmp->right);
            }
        }

        depth++;

        if (depth == n)
        {
            return q.size();
        }
    }

    return 0;
}
int levelmaxnum(int root[], int size)
{
    // 我们有一个数组,需要找它的宽
    // 维护一个最大宽,一个队列
    queue<int> qu;
    int cur, rchild, lchild;
    int m = 0;
    int qsize = 0;
    if (root == nullptr || size <= 0)
    {
        return 0;
    }
    if (root[1] == 0)
    {
        return 0;
    }
    qu.push(1);
    while (!qu.empty())
    {
        qsize = qu.size();
        m = max(m, qsize);
        // 更新最大值
        for (int i = 0; i < qsize; i++)
        {
            cur = qu.front(); // 取出第一个索引
            lchild = cur * 2;
            rchild = lchild + 1;
            if (lchild < size && root[lchild] != 0)
            {
                qu.push(lchild);
            }
            if (rchild < size && root[rchild] != 0)
            {
                qu.push(rchild);
            }
        }
    }
    return m;
}