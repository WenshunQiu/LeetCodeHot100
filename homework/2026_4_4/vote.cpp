#include <deque>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
    deque<int> R;
    deque<int> D;
    char c;
    int n = 0;
    int length = 0;
    string senate;
    cin >> senate;
    length = senate.size();
    for (int i = 0; i < length; i++)
    {
        if (senate[i] == 'R')
        {
            R.push_back(i);
        }
        else
        {
            D.push_back(i);
        }
    }
    while (!R.empty() && !D.empty())
    {
        if (R.front() < D.front())
        {
            R.push_back(R.front() + length);
            R.pop_front();
            D.pop_front();
        }
        else
        {
            D.push_back(D.front() + length);
            D.pop_front();
            R.pop_front();
        }
    }
    cout << (R.empty() ? "Dire" : "Radiant") << endl;
    return 0;
}