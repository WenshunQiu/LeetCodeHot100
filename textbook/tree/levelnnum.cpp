#include <string>
#include <iostream>
#include <queue>
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
