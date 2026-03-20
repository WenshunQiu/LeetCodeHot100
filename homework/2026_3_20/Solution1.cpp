#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;
vector<int> twoSum(vector<int> &nums, int target);

int main(int argc, char const *argv[])

{
    ifstream fin("in.txt");
    string numsLine, targetLine;
    while (getline(fin, numsLine))
    {
        if (!getline(fin, targetLine))
            break;
        vector<int> nums;
        if (!numsLine.empty())
        {
            stringstream ss(numsLine);
            int x;
            while (ss >> x)
            {
                nums.push_back(x);
            }
        }
        int target = stoi(targetLine);
        vector<int> ans = twoSum(nums, target);
        cout << ans[0] << " " << ans[1] << endl;
    }

    fin.close();
    return 0;
}

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++)
    {
        if (map.count(target - nums[i]))
        {
            return {map[target - nums[i]], i};
        }
        map[nums[i]] = i;
    }
    return {-1, -1};
}
