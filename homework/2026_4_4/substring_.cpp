#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <deque>
using namespace std;

int main()
{
    vector<int> nums;
    string line;
    getline(cin, line);
    stringstream ss(line);

    int x;
    while (ss >> x)
    {
        nums.push_back(x);
    }

    long long k;
    cin >> k;
    //-------------读取数据完成
    int n = nums.size();

    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    deque<int> q;

    // 最短长度
    int ans = n + 1;

    for (int i = 0; i <= n; i++)
    {
        while (!q.empty() && prefix[i] - prefix[q.front()] >= k)
        {
            ans = min(ans, i - q.front());
            q.pop_front();
        }

        // 维护队列单调递增
        while (!q.empty() && prefix[i] <= prefix[q.back()])
        {
            q.pop_back();
        }
        q.push_back(i);
    }

    if (ans == n + 1)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }

    return 0;
}