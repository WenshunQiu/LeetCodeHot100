#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int k;
    cin >> k;

    vector<long long> cnt(n + 1, 0);
    cnt[0] = 1;

    int odd = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        odd += (nums[i] & 1);
        if (odd >= k) {
            ans += cnt[odd - k];
        }
        cnt[odd]++;
    }

    cout << ans << '\n';
    return 0;
}
