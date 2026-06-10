#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
    }
    Node(int x)
    {
        val = x;
    }
};

void makeAdjList(string s, vector<vector<int>> &adj)
{
    vector<int> row;
    int depth = 0;
    int num = 0;
    int flag = 0;
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            num = num * 10 + s[i] - '0';
            flag = 1;
        }
        else
        {
            if (flag)
            {
                row.push_back(num);
                num = 0;
                flag = 0;
            }
            if (s[i] == '[')
            {
                depth++;
                if (depth == 2)
                {
                    row.clear();
                }
            }
            else if (s[i] == ']')
            {
                if (depth == 2)
                {
                    adj.push_back(row);
                }
                depth--;
            }
        }
    }
}

Node *makeGraph(vector<vector<int>> &adj, vector<Node *> &nodes)
{
    int n = adj.size();
    if (n == 0)
    {
        return nullptr;
    }
    nodes.resize(n + 1, nullptr);
    for (int i = 1; i <= n; i++)
    {
        nodes[i] = new Node(i);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < (int)adj[i - 1].size(); j++)
        {
            int v = adj[i - 1][j];
            nodes[i]->neighbors.push_back(nodes[v]);
        }
    }
    return nodes[1];
}

Node *cloneDfs(Node *p, vector<Node *> &copyNodes)
{
    if (p == nullptr)
    {
        return nullptr;
    }
    if (copyNodes[p->val] != nullptr)
    {
        return copyNodes[p->val];
    }
    Node *q = new Node(p->val);
    copyNodes[p->val] = q;
    for (int i = 0; i < (int)p->neighbors.size(); i++)
    {
        q->neighbors.push_back(cloneDfs(p->neighbors[i], copyNodes));
    }
    return q;
}

Node *cloneGraph(Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    vector<Node *> copyNodes(105, nullptr);
    return cloneDfs(node, copyNodes);
}

void graphToAdjList(Node *node, vector<vector<int>> &adj)
{
    if (node == nullptr)
    {
        return;
    }
    vector<Node *> que;
    vector<int> vis(105, 0);
    que.push_back(node);
    vis[node->val] = 1;
    int front = 0;
    int maxVal = 0;
    while (front < (int)que.size())
    {
        Node *p = que[front++];
        if (p->val > maxVal)
        {
            maxVal = p->val;
        }
        for (int i = 0; i < (int)p->neighbors.size(); i++)
        {
            Node *q = p->neighbors[i];
            if (!vis[q->val])
            {
                vis[q->val] = 1;
                que.push_back(q);
            }
        }
    }
    adj.resize(maxVal);
    for (int i = 0; i < (int)que.size(); i++)
    {
        Node *p = que[i];
        for (int j = 0; j < (int)p->neighbors.size(); j++)
        {
            adj[p->val - 1].push_back(p->neighbors[j]->val);
        }
    }
}

void printAdjList(vector<vector<int>> &adj)
{
    cout << "[";
    for (int i = 0; i < (int)adj.size(); i++)
    {
        cout << "[";
        for (int j = 0; j < (int)adj[i].size(); j++)
        {
            cout << adj[i][j];
            if (j != (int)adj[i].size() - 1)
            {
                cout << ",";
            }
        }
        cout << "]";
        if (i != (int)adj.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "]";
}

void freeGraph(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    vector<Node *> que;
    vector<int> vis(105, 0);
    que.push_back(node);
    vis[node->val] = 1;
    int front = 0;
    while (front < (int)que.size())
    {
        Node *p = que[front++];
        for (int i = 0; i < (int)p->neighbors.size(); i++)
        {
            Node *q = p->neighbors[i];
            if (!vis[q->val])
            {
                vis[q->val] = 1;
                que.push_back(q);
            }
        }
    }
    for (int i = 0; i < (int)que.size(); i++)
    {
        delete que[i];
    }
}

int main()
{
    string s;
    getline(cin, s);
    vector<vector<int>> adj;
    makeAdjList(s, adj);

    vector<Node *> nodes;
    Node *head = makeGraph(adj, nodes);
    Node *newHead = cloneGraph(head);

    vector<vector<int>> newAdj;
    graphToAdjList(newHead, newAdj);
    printAdjList(newAdj);

    freeGraph(head);
    freeGraph(newHead);
    return 0;
}
