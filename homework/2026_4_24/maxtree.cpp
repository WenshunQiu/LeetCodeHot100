#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    TreeNode *build(vector<int> &nums, int left, int right)
    {
        if (left > right)
            return nullptr;

        int maxIndex = left;

        for (int i = left; i <= right; i++)
        {
            if (nums[i] > nums[maxIndex])
            {
                maxIndex = i;
            }
        }

        TreeNode *root = new TreeNode(nums[maxIndex]);

        root->left = build(nums, left, maxIndex - 1);
        root->right = build(nums, maxIndex + 1, right);

        return root;
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        return build(nums, 0, nums.size() - 1);
    }
};

string serialize_BFS(TreeNode *root)
{
    if (!root)
        return "[]";

    vector<string> res;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *cur = q.front();
        q.pop();

        if (cur)
        {
            res.push_back(to_string(cur->val));
            q.push(cur->left);
            q.push(cur->right);
        }
        else
        {
            res.push_back("null");
        }
    }

    while (!res.empty() && res.back() == "null")
    {
        res.pop_back();
    }

    string ans = "[";
    for (int i = 0; i < res.size(); i++)
    {
        if (i > 0)
            ans += ",";
        ans += res[i];
    }
    ans += "]";

    return ans;
}

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution sol;
    TreeNode *root = sol.constructMaximumBinaryTree(nums);

    cout << serialize_BFS(root) << endl;

    return 0;
}