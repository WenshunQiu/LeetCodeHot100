#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    int l = 0, r = n - 1;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] > nums[mid + 1])
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << endl;
}