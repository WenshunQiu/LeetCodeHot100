#include <iostream>
#include <cstring>
#define M 1000000007
using namespace std;
int islegal(char op[], int n)
{
    int i = 0;
    int hasNum = 0;
    while (i < n)
    {
        switch (op[i])
        {
        case 'I':
            hasNum++;
            break;
        case 'O':
            if (!hasNum)
            {
                return 0;
            }
            hasNum--;
            break;
        default:
            break;
        }
        i++;
    }
    if (hasNum)
    {
        return 0;
    }
    return 1;
}
// AD合法
