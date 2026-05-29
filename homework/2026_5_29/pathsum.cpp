#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef struct Node
{
    int data;
    struct Node *lchild;
    struct Node *rchild;
    Node(int n)
    {
        data = n;
        lchild = nullptr;
        rchild = nullptr;
    }
} Node;

vector<vector<int>> ways;
vector<int> tempWay;
int nowlen = 0;
void dfs(Node *root, int len)
{
    if (root == nullptr)
    {
        return;
    }
    nowlen += root->data;
    tempWay.push_back(root->data);
    if (nowlen == len)
    {
        if (root->lchild == nullptr && root->rchild == nullptr)
        {
            ways.push_back(tempWay);
            tempWay.pop_back();
            nowlen -= root->data;
            return;
        }
    }
    if (nowlen < len)
    {
        dfs(root->lchild, len);
        dfs(root->rchild, len);
        tempWay.pop_back();
        nowlen -= root->data;
        return;
    }
    if (nowlen > len)
    {
        tempWay.pop_back();
        nowlen -= root->data;
        return;
    }
}

int main()
{
    int sum, n;
    cin >> sum >> n;
    vector<string> nums_string(n);
    for (int i = 0; i < n; i++) // 获取数据
    {
        cin >> nums_string[i];
    }
    // 建树

    if (nums_string[0] == "null")
    {
        return 0;
    }

    Node *root = new Node(stoi(nums_string[0]));
    queue<Node *> q;
    q.push(root);
    int index = 1;
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (index < n && nums_string[index] != "null")
        {
            temp->lchild = new Node(stoi(nums_string[index]));
            q.push(temp->lchild);
        }
        index++;
        if (index < n && nums_string[index] != "null")
        {
            temp->rchild = new Node(stoi(nums_string[index]));
            q.push(temp->rchild);
        }
        index++;
    }
    /* 对于每个点，加上数据，如果现在的和还没到，就先找左孩子，然后找右孩子。
    如果到了，并且是叶子节点，就存储路径，如果不是叶子节点，就回退，
    如果超了，就回退，并走右孩子；
     */
    dfs(root, sum);
    cout << '[';
    for (int i = 0; i < (int)ways.size(); i++)
    {
        cout << '[';
        for (int j = 0; j < (int)ways[i].size(); j++)
        {
            if (j)
                cout << ',';
            cout << ways[i][j];
        }
        cout << ']';
        if (i + 1 < (int)ways.size())
            cout << ',';
    }
    cout << ']';
}