#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

void getInput(vector<long long> &nums)
{
    int len;
    scanf("%d", &len);
    for (int i = 0; i < len; i++)
    {
        long long num;
        scanf("%lld", &num);
        nums.push_back(num);
    }
}

long long calcMax(const vector<long long> &nums)
{
    priority_queue<long long, vector<long long>, greater<long long>> pq(nums.begin(), nums.end());
    while (pq.size() > 1)
    {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();
        pq.push(a * b + 1);
    }
    return pq.top();
}

long long calcMin(const vector<long long> &nums)
{
    priority_queue<long long> pq(nums.begin(), nums.end());
    while (pq.size() > 1)
    {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();
        pq.push(a * b + 1);
    }
    return pq.top();
}

int main()
{
    vector<long long> nums;
    getInput(nums);
    long long ans = calcMax(nums) - calcMin(nums);
    printf("%lld", ans);
}
/*
时间复杂度和空间复杂度如下：
calcMax：建堆 O(n)，循环 n-1 次，每次 2 次 pop + 1 次 push，每次都是 O(log n)，所以总计 O(n log n)。
calcMin：同理也是 O(n log n)。
主程序调用两次，所以总时间复杂度仍是 O(n log n)（常数约 2 倍）。
空间复杂度：
两个函数各自维护一个优先队列，规模最多 n，所以单次是 O(n)。
程序整体辅助空间复杂度是 O(n)。
*/