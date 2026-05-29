#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef int State;
typedef struct Node
{
    int data;
    struct Node *lchild;
    struct Node *rchild;
    Node(int num)
    {
        data = num;
        lchild = nullptr;
        rchild = nullptr;
    }
} Node;
enum
{
    OK,
    ERROR,
};

State inputData(Node *&Root)
{
    vector<string> nums;
    string str;
    if (!getline(cin, str))
    {
        Root = nullptr;
        return ERROR;
    }
    while (str.empty() && cin.good())
    {
        getline(cin, str);
    }

    str = str.substr(1, str.length() - 2);
    replace(str.begin(), str.end(), ',', ' ');
    stringstream ss(str);
    string token;
    while (ss >> token)
    {
        nums.push_back(token);
    }

    if (nums.empty() || nums[0] == "null")
    {
        Root = nullptr;
        return ERROR;
    }

    Node *root = new Node(stoi(nums[0]));
    queue<Node *> qu;
    qu.push(root);
    int i = 1;
    while (!qu.empty() && i < (int)nums.size())
    {
        Node *cur = qu.front();
        qu.pop();
        if (i < (int)nums.size() && nums[i] != "null")
        {
            cur->lchild = new Node(stoi(nums[i]));
            qu.push(cur->lchild);
        }
        i++;
        if (i < (int)nums.size() && nums[i] != "null")
        {
            cur->rchild = new Node(stoi(nums[i]));
            qu.push(cur->rchild);
        }
        i++;
    }
    Root = root;
    return OK;
}

Node *findTarget(Node *root, int target)

{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->data == target)
    {
        return root;
    }
    else
    {
        Node *left = findTarget(root->lchild, target);
        if (left != nullptr)
        {
            return left;
        }
        return findTarget(root->rchild, target);
    }
}

vector<int> getDistanceKNode(Node *root, Node *target, int distance)
{
    vector<int> ans;
    if (root == nullptr || target == nullptr || distance < 0)
    {
        return ans;
    }

    unordered_map<Node *, Node *> map;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        if (cur->lchild != nullptr)
        {
            map[cur->lchild] = cur;
            q.push(cur->lchild);
        }
        if (cur->rchild != nullptr)
        {
            map[cur->rchild] = cur;
            q.push(cur->rchild);
        }
    }

    unordered_set<Node *> visited;
    queue<Node *> bfs;
    bfs.push(target);
    visited.insert(target);

    int curDist = 0;
    while (!bfs.empty())
    {
        int sz = (int)bfs.size();
        if (curDist == distance)
        {
            while (sz--)
            {
                ans.push_back(bfs.front()->data);
                bfs.pop();
            }
            break;
        }

        while (sz--)
        {
            Node *cur = bfs.front();
            bfs.pop();

            if (cur->lchild != nullptr && !visited.count(cur->lchild))
            {
                visited.insert(cur->lchild);
                bfs.push(cur->lchild);
            }
            if (cur->rchild != nullptr && !visited.count(cur->rchild))
            {
                visited.insert(cur->rchild);
                bfs.push(cur->rchild);
            }
            if (map.count(cur) && !visited.count(map[cur]))
            {
                visited.insert(map[cur]);
                bfs.push(map[cur]);
            }
        }
        curDist++;
    }

    sort(ans.begin(), ans.end());
    return ans;
}

int main()
{
    Node *root = nullptr;
    inputData(root);

    int targetNum;
    int k;
    cin >> targetNum >> k;

    Node *target = findTarget(root, targetNum);
    vector<int> ans = getDistanceKNode(root, target, k);
    cout << '[';
    for (int i = 0; i < (int)ans.size(); i++)
    {
        if (i)
        {
            cout << ",";
        }
        cout << ans[i];
    }
    cout << ']' << endl;
    return 0;
}
