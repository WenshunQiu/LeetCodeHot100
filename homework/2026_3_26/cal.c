#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_OP 100

char opStk[MAX_OP];

int numStk[MAX_OP];

int opTop = -1;
int numTop = -1;

int getPriority(char op)
{
    switch (op)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    default:
        return -1;
    }
}

void pushOp(char op) { opStk[++opTop] = op; }
char popOp() { return opStk[opTop--]; }
char peekOp() { return opStk[opTop]; }

void pushNum(int num) { numStk[++numTop] = num; }
int popNum() { return numStk[numTop--]; }
int peekNum() { return numStk[numTop]; }

int calc(int a, int b, char op)
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
        return a / b;
    case '%':
        return a % b;
    default:
        return -1;
    }
}

int fcal(char *exp)
{
    int i = 0;
    int len = strlen(exp);
    while (i < len)
    {

        if (exp[i] == ' ')
        {
            i++;
            continue;
        }

        if (exp[i] == '=')
        {
            break;
        }

        if (isdigit(exp[i]))
        {
            int num = 0;
            while (i < len && isdigit(exp[i])) // 从字符串数字转为普通数字，需要从最高位读取，所以需要x10
            {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            pushNum(num);
        }

        else if (exp[i] == '(')
        {
            pushOp(exp[i]);
            i++;
        }

        else if (exp[i] == ')')
        {
            while (opTop != -1 && peekOp() != '(')
            {
                char op = popOp();
                int b = popNum();
                int a = popNum();
                pushNum(calc(a, b, op));
            }
            popOp();
            i++;
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%')
        {
            while (opTop != -1 && getPriority(peekOp()) >= getPriority(exp[i]))//如果栈内的优先级大于当前的优先级，则计算栈内的
            {
                char op = popOp();
                int b = popNum();
                int a = popNum();
                pushNum(calc(a, b, op));
            }
            pushOp(exp[i]);
            i++;
        }
    }

    while (opTop != -1)
    {
        char op = popOp();
        int b = popNum();
        int a = popNum();
        pushNum(calc(a, b, op));
    }

    return numStk[numTop];
}

int main()
{
    char exp[1000];
    fgets(exp, 1000, stdin);
    printf("%d\n", fcal(exp));
    return 0;
}