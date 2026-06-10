#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

const int MOD = 1000000007;

int n;
int minProfit;
int group[105];
int profit[105];
int groupIndex = 0;
int profitIndex = 0;

void makeInput()
{
    memset(group, 0, sizeof(group));
    memset(profit, 0, sizeof(profit));
    groupIndex = 0;
    profitIndex = 0;
    string s;
    getline(cin, s);

    int i = 0;
    int numberCount = 0;
    while (i < (int)s.size())
    {
        if (isdigit(s[i]))
        {
            int num = 0;
            while (i < (int)s.size() && isdigit(s[i]))
            {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if (numberCount == 0)
            {
                n = num;
            }
            else if (numberCount == 1)
            {
                minProfit = num;
            }
            else
            {
                int leftBracket = 0;
                for (int j = 0; j < i; j++)
                {
                    if (s[j] == '[')
                    {
                        leftBracket++;
                    }
                }
                if (leftBracket == 1)
                {
                    group[groupIndex++] = num;
                }
                else
                {
                    profit[profitIndex++] = num;
                }
            }
            numberCount++;
        }
        else
        {
            i++;
        }
    }
}

int profitableSchemes()
{
    int dp[105][105];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i < groupIndex; i++)
    {
        int members = group[i];
        int earn = profit[i];
        for (int j = n; j >= members; j--)
        {
            for (int k = minProfit; k >= 0; k--)
            {
                int lastProfit = k - earn;
                if (lastProfit < 0)
                {
                    lastProfit = 0;
                }
                dp[j][k] = (dp[j][k] + dp[j - members][lastProfit]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= n; j++)
    {
        ans = (ans + dp[j][minProfit]) % MOD;
    }
    return ans;
}

int main()
{
    makeInput();
    cout << profitableSchemes();
    return 0;
}
