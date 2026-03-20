#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[])

{
    vector<int> allNum;

    for (int i = 0; i < 2; i++)
    {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            allNum.push_back(temp);
        }
    }
    sort(allNum.begin(), allNum.end());
    for (auto &&i : allNum)
    {
        cout << i << " ";
    }
    

    return 0;
}
