#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <string>
using namespace std;
struct Employee
{
    int id;
    int importance;
    vector<int> subordinates;
};
unordered_map<int, Employee *> mp;
// DFS
int dfs(int id)
{
    Employee *employee = mp[id];
    int sum = employee->importance;
    for (int subordinate : employee->subordinates)
    {
        sum += dfs(subordinate);
    }
    return sum;
}

int parseNumber(const string &s, int &i)
{
    int sign = 1;
    if (s[i] == '-')//检查负数
    {
        sign = -1;
        i++;
    }
    int num = 0;
    while (i < (int)s.size() && isdigit(s[i]))
    {
        num = num * 10 + (s[i] - '0');
        i++;
    }
    return sign * num;
}
int main()
{
    string line;
    getline(cin, line);

    // 找到employees
    int pos = line.find("[[");
    int endPos = line.find("]], ");
    if (pos == string::npos || endPos == string::npos)
    {
        return 0;
    }
    string empStr = line.substr(pos, endPos - pos + 2); //[[1,5,[2,3]],[2,3,[]],[3,3,[]]]

    // 找到id
    int idPos = line.find("id = ");
    int targetId = idPos == string::npos ? 0 : stoi(line.substr(idPos + 5));

    vector<Employee *> employees;
    int i = 0;
    while (i < (int)empStr.size())
    {
        // 找到一个员工的开始：[数字,数字,[...]]
        if (empStr[i] == '[' && i + 1 < (int)empStr.size() && (isdigit(empStr[i + 1]) || empStr[i + 1] == '-'))
        {
            i++; // 跳过 '['

            // 解析 id
            int id = parseNumber(empStr, i);

            if (empStr[i] == ',')
                i++;

            // 解析 importance
            int importance = parseNumber(empStr, i);

            if (empStr[i] == ',')
                i++;
            if (empStr[i] == '[')
                i++; // 进入 subordinate 列表

            vector<int> subs;
            while (i < (int)empStr.size() && empStr[i] != ']')
            {
                if (empStr[i] == ',')
                {
                    i++;
                }
                else if (isdigit(empStr[i]) || empStr[i] == '-')
                {
                    int subId = parseNumber(empStr, i);
                    subs.push_back(subId);
                }
                else
                {
                    i++;
                }
            }

            if (i < (int)empStr.size() && empStr[i] == ']')
                i++; // 跳过 subordinate 的 ]
            if (i < (int)empStr.size() && empStr[i] == ']')
                i++; // 跳过员工的 ]

            Employee *emp = new Employee();
            emp->id = id;
            emp->importance = importance;
            emp->subordinates = subs;

            employees.push_back(emp);
            mp[id] = emp;
        }
        else
        {
            i++;
        }
    }
    cout << dfs(targetId) << endl;
    return 0;
}