#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#define M 10000
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> strs[i];
    }
    unordered_map<string, vector<string>> map;
    vector<string> order;
    for (auto i : strs)
    {
        string s = i;
        sort(s.begin(), s.end());
        if (map.find(s) == map.end())
        {
            order.push_back(s);
        }
        map[s].push_back(i);
    }
    for (auto i : order)
    {
        for (auto j : map[i])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
    }

