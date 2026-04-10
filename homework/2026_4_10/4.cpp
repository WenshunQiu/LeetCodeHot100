#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 辅助函数：判断字符串是否为回文（双指针）
bool isPalindrome(const string &s)
{
    int l = 0, r = s.size() - 1;
    while (l < r)
    {
        if (s[l] != s[r])
            return false;
        l++;
        r--;
    }
    return true;
}

// 辅助函数：反转字符串
string reverseStr(const string &s)
{
    return string(s.rbegin(), s.rend());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // 加速输入输出

    int n;
    cin >> n;
    vector<string> words(n);
    unordered_map<string, int> word2idx; // 哈希表：字符串 -> 索引

    // 1. 读取输入 + 处理空串（输入""转换为空字符串）
    for (int i = 0; i < n; ++i)
    {
        cin >> words[i];
        if (words[i] == "\"\"")
        { // 题目特殊约定：空串输入为""
            words[i] = "";
        }
        word2idx[words[i]] = i;
    }

    vector<pair<int, int>> res; // 存储结果

    // 2. 遍历每个字符串，分割并查找匹配
    for (int i = 0; i < n; ++i)
    {
        const string &word = words[i];
        int len = word.size();

        // 分割点 k：left = word[0:k], right = word[k:len]
        for (int k = 0; k <= len; ++k)
        {
            string left = word.substr(0, k);
            string right = word.substr(k);

            // 情况1：left是回文 → 找 right 的反转串 → 拼接后 [j, i] 是回文
            if (isPalindrome(left))
            {
                string rev_right = reverseStr(right);
                // 查找是否存在该字符串，且索引不等于i
                if (word2idx.count(rev_right))
                {
                    int j = word2idx[rev_right];
                    if (j != i)
                    {
                        res.emplace_back(j, i);
                    }
                }
            }

            // 情况2：right是回文 → 找 left 的反转串 → 拼接后 [i, j] 是回文
            // 额外判断 k != len：避免和情况1重复（分割点为len时重复）
            if (isPalindrome(right) && k != len)
            {
                string rev_left = reverseStr(left);
                if (word2idx.count(rev_left))
                {
                    int j = word2idx[rev_left];
                    if (j != i)
                    {
                        res.emplace_back(i, j);
                    }
                }
            }
        }
    }

    // 3. 按题目要求排序：i升序，i相同则j升序
    sort(res.begin(), res.end());

    // 4. 输出结果
    cout << res.size() << "\n";
    for (auto &p : res)
    {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}