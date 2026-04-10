#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

int isPalindrome(const string &s)
{
    int l = 0, r = s.length() - 1;
    while (l < r)
    {
        if (s[l] != s[r])
            return false;
        l++;
        r--;
    }
    return true;
}
string reverseStr(const string &s) { return string(s.rbegin(), s.rend()); }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 加速输入输出

    int n;
    cin >> n;
    vector<string> words(n);

    unordered_map<string, int> map;

    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
        if (words[i] == "\"\"")
        {
            words[i] = "";
        }
        map[words[i]] = i;
    }

    vector<pair<int, int>> ans;

    for (int i = 0; i < n; i++)
    {
        const string &word = words[i];
        string left, right;
        for (int k = 0; k <= word.size(); k++)
        {
            left = word.substr(0, k);
            right = word.substr(k);
            if (isPalindrome(left))
            {
                string rev_right = reverseStr(right);
                if (map.count(rev_right))
                {
                    int index = map[rev_right];
                    if (index != i)
                    {
                        ans.emplace_back(index, i);
                    }
                }
            }
            if (isPalindrome(right) && k != word.size())
            {
                string rev_left = reverseStr(left);
                if (map.count(rev_left))
                {
                    int index = map[rev_left];
                    if (index != i)
                    {
                        ans.emplace_back(i, index);
                    }
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto &p : ans)
    {
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}