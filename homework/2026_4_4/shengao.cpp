#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> people(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> people[i][0] >> people[i][1];
    }

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    });

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++)
    {
        ans.insert(ans.begin() + people[i][1], people[i]);
    }

    for (int i = 0; i < n; i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}