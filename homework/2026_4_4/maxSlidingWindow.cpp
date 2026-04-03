#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int> nums;
    string numStr;
    getline(cin, numStr);
    stringstream iss(numStr);
    int num;
    while (iss >> num)
    {
        nums.push_back(num);
    }
    int windowSize;
    cin >> windowSize;
    //-----------输入数据
    vector<int> maxWindow;
    deque<int> deq;
    for (int right = 0; right < nums.size(); right++)
    {
        while (!deq.empty() && deq.front() <= right - windowSize)
        {
            deq.pop_front();
        } // 头掉了就砍头

        while (!deq.empty() && nums[deq.back()] < nums[right])
        {
            deq.pop_back();
        } // 尾小了就砍尾

        deq.push_back(right); // 下标！进去deq

        if (right >= windowSize - 1)
        {
            maxWindow.push_back(nums[deq.front()]);
        } // 够窗口就存
    }
    for (auto i : maxWindow)
    {
        cout << i << " ";
    }

    return 0;
}
