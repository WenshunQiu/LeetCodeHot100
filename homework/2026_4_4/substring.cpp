#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <deque>
using namespace std;
int main()
{
    vector<int> nums;
    string numstr;
    getline(cin, numstr);
    stringstream ss(numstr);
    int num;
    while (ss >> num)
    {
        nums.push_back(num);
    }
    long long minSum = 0;
    cin >> minSum;
    //-----------读取数据完成
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    deque<int> dq; // 存储前缀和下标，且对应的前缀和单调递增
    int ans = n + 1;

    for (int i = 0; i <= n; i++)
    {
        // 当前前缀和与队头前缀和之差 >= k，说明找到一个满足条件的子数组
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= minSum)
        {
            ans = min(ans, i - dq.front());
            dq.pop_front();//队伍头已经被使用过了，弹出。
        }

        // 保持队列中前缀和单调递增
        while (!dq.empty() && prefix[i] <= prefix[dq.back()])//如果更小，那么更容易满足条件，应该弹出队尾元素。
        {
            dq.pop_back();
        }

        dq.push_back(i);
    }

    cout << (ans == n + 1 ? -1 : ans) << endl;

    return 0;
}