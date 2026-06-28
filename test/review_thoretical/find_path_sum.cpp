#include "textbook/tree/tree.hpp"
#include <iostream>
#include <vector>
using namespace std;

int sum = 0;
vector<int> currentPath;
vector<vector<int>> result;
// 这个是求从根到叶子节点的路径和，如果要求任意路段可能需要用到哈希表或者使用双重dfs
void findPathSumInTree(BTNode *root, int target)
{
    if (root == nullptr)
    {
        return;
    }
    sum += root->data;
    currentPath.push_back(root->data);
    // 如果是叶子节点且路径和等于target，保存结果
    if (root->lchild == nullptr && root->rchild == nullptr && sum == target)
    {
        result.push_back(currentPath);
    }
    // 递归左右子树
    findPathSumInTree(root->lchild, target);
    findPathSumInTree(root->rchild, target);
    // 回溯
    sum -= root->data;
    currentPath.pop_back();
}

vector<int> path;
vector<vector<int>> res;
// 思路是一路计算过去，分为两种情况，一种是选择，另一种是不选择，那就可以在递归的时候包含所有情况了.
void backTrack(int idx, int sum, vector<int> &nums, int target)
{
    if (sum == target)
    {
        res.push_back(path);
        return;
    }
    if (idx >= nums.size() || sum > target)
    {
        return;
    }
    path.push_back(nums[idx]);
    backTrack(idx + 1, sum + nums[idx], nums, target);
    path.pop_back();
    backTrack(idx + 1, sum, nums, target);
}
// 也可以使用动态规划：
// 但是动态规划无法输出实现等于的数组
bool hasSubsetSum(vector<int> &nums, int target)
{
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (auto &&num : nums)
    {
        for (int i = target; i >= num; i--) // 倒序计算可以保证每个数字都只被计算一次
        {
            dp[i] = dp[i] || dp[i - num]; // 要么已经实现了，要么加上当前的数字才可以实现
        }
    }
    return dp[target];
}