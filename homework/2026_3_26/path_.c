#include <stdio.h>
#include <string.h>

#define MAX 1000

typedef struct
{
    int dir;
    int len;
} Step;

Step stk[MAX];
int top = -1;

int isOpposite(int a, int b)
{
    if (a == 1 && b == 2)
        return 1;
    if (a == 2 && b == 1)
        return 1;
    if (a == 3 && b == 4)
        return 1;
    if (a == 4 && b == 3)
        return 1;
    return 0;
}

int reverseDir(int d)
{
    if (d == 1)
        return 2;
    if (d == 2)
        return 1;
    if (d == 3)
        return 4;
    if (d == 4)
        return 3;
    return 0;
}

int main()
{
    
}
