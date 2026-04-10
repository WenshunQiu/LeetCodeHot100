#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 数字到字母的映射表
const string phoneMap[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

/**
 * 回溯函数
 * @param digits 输入的数字字符串
 * @param index 当前处理到 digits 的第几位
 * @param current 当前正在构建的字母组合
 */
void backtrack(const string& digits, int index, string& current) {
    // 终止条件：当前组合长度等于输入数字的长度
    if (index == digits.length()) {
        cout << current << endl; // 按要求：每行输出一个组合
        return;
    }

    // 获取当前数字对应的字母字符串
    int digit = digits[index] - '0';
    const string& letters = phoneMap[digit];

    // 遍历当前数字对应的所有字母
    for (char c : letters) {
        current.push_back(c);       // 做选择：添加字母
        backtrack(digits, index + 1, current); // 递归：处理下一个数字
        current.pop_back();         // 撤销选择：回溯，移除最后一个字母
    }
}

int main() {
    string digits;
    // 如果需要在本地测试，可以解开下面两行的注释
    // cout << "Enter digits: ";
    // cin >> digits;
    
    // 为了演示，这里假设输入为 "23"，你可以修改这里或启用上面的 cin
    digits = "23"; 

    if (digits.empty()) {
        return 0;
    }

    string current;
    backtrack(digits, 0, current);

    return 0;
}