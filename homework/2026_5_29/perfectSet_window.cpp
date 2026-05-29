#include <iostream>
#include <vector>
using namespace std;

long long atMostKOdd(const vector<int>& nums, int k) {
    if (k < 0) return 0;

    int left = 0;
    int odd = 0;
    long long count = 0;

    for (int right = 0; right < (int)nums.size(); right++) {
        odd += (nums[right] & 1);
        while (odd > k) {
            odd -= (nums[left] & 1);
            left++;
        }
    }

    return count;
}

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int k;
    cin >> k;

    long long ans = atMostKOdd(nums, k) - atMostKOdd(nums, k - 1);
    cout << ans << '\n';
    return 0;
}
