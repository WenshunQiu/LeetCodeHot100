#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int main()
{
    int len = 0;
    cin >> len;
    int *heights = new int[len];
    for (int i = 0; i < len; i++)
    {
        cin >> heights[i];
    }
    //------输入数据完毕-------
    int ans = 0;
    deque<int> hsta = {0};
    for (int i = 0; i <= len; i++)
    {
        int h = i == len ? 0 : heights[i];
        if (hsta.empty() || h >= heights[hsta.back()])
        {
            hsta.push_back(i);
        }
        else
        {
            int t = hsta.back();
            hsta.pop_back();
            ans = max(ans, heights[t] * (hsta.empty() ? i : i - hsta.back() - 1));
            i--;//到递减处就往递增处检查，直到当前高度满足递增后加入.
        }
    }
    cout << ans << endl;
}