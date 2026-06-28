#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

int getPriority(char op)
{
    if (op == '(')
    {
        return 0;
    }
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    return -1;
}

double calc(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            printf("WDF");
            exit(-1);
        }
        return a / b;
    default:
        break;
    }
}

double dijkstraEval(string s)
{
    stack<double> val_st;
    stack<char> op_st;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if (c == ' ')
        {
            continue;
        }
        if ((c <= '9' && c >= '0') || c == '.')
        {
            double num = 0;
            double dec = 1;
            int pos = i;
            while (pos < n && s[pos] >= '0' && s[pos] <= '9')
            {
                num = num * 10 + (s[pos] - '0');
                pos++;
            }
            if (pos < n && s[pos] == '.')
            {
                pos++;
                while (pos < n && s[pos] >= '0' && s[pos] <= '9')
                {
                    dec /= 10;
                    num += (s[pos] - '0') * dec;
                    pos++;
                } // 这个处理小数的逻辑很优雅啊；
            }
            val_st.push(num);
            i = pos - 1; // 因为在每次处理完数据后都多加了一个1，所以这里要减去一个1；
        }
        else if (c == '(')
        {
            op_st.push(c);
        }
        else if (c == ')')
        {
            while (op_st.top() != '(')
            {
                char op = op_st.top();
                op_st.pop();
                double b = val_st.top();
                val_st.pop();
                double a = val_st.top();
                val_st.pop();
                val_st.push(calc(a, b, op));
            }
            op_st.pop();
        }
        else if (getPriority(c) > 0)
        {
            while (!op_st.empty() && getPriority(op_st.top()) >= getPriority(c)) // 每一次的计算之前，都要做好可能越界的打算，这里一定要检测op_st是否为空;
            {
                char op = op_st.top();
                op_st.pop();
                double b = val_st.top();
                val_st.pop();
                double a = val_st.top();
                val_st.pop();
                val_st.push(calc(a, b, op));
            }
            op_st.push(c);
        }
    }
    while (!op_st.empty())
    {
        char op = op_st.top();
        op_st.pop();
        double b = val_st.top();
        val_st.pop();
        double a = val_st.top();
        val_st.pop();
        val_st.push(calc(a, b, op));
    }
    return val_st.top();
}

int main()
{
    string exp;
    printf("input ur exp: ");
    cin >> exp;  // 使用 cin 读取 string，或者用 getline(cin, exp) 读取含空格的表达式
    double res = dijkstraEval(exp);
    printf("answer is %.2f\n", res);
    return 0;
}