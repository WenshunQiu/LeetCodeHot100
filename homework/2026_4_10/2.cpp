#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s, t;
    getline(cin, s);
    getline(cin, t);

    if (s == "\"\"") s = "";
    if (t == "\"\"") t = "";

    int n = t.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1; 
    for (char ch : s) {
        for (int j = n; j >= 1; --j) {
            if (ch == t[j - 1]) {
                dp[j] += dp[j - 1];
            }
        }
    }

    cout << dp[n] << endl;
    return 0;
}