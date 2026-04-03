#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int main()
{
    int n, chuangkou;
    cin >> n >> chuangkou;
    vector<int> times(n);
    for (int i = 0; i < n; i++)
    {
        cin >> times[i];
    }
    sort(times.begin(), times.end());
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < chuangkou; i++)
    {
        q.push(0);
    }
    int total = 0;
    for (auto &&i : times)
    {
        int cur = q.top();
        q.pop();
        total += cur;
        q.push(cur + i);
    }
    cout << total << endl;
    
}