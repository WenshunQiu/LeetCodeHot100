#include <stdio.h>
#include <string.h>

#define MAX 1000

typedef struct
{
    int dir;
    int step;
} Step;

Step stack[MAX];
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
    int d, s;
    char token[20];

    while (1)
    {
        scanf("%s", token);
        sscanf(token, "%d-%d", &d, &s);
        if (d == 0 && s == 0)
            break;

        while (s > 0 && top != -1 && isOpposite(stack[top].dir, d))
        {
            if (stack[top].step > s)
            {
                stack[top].step -= s;
                s = 0;
            }
            else if (stack[top].step == s)
            {
                top--;
                s = 0;
            }
            else
            {
                s -= stack[top].step;
                top--;
            }
        }

        if (s > 0)
        {
            if (top >= 0 && stack[top].dir == d)
            {
                stack[top].step += s;
            }
            else
            {
                top++;
                stack[top].dir = d;
                stack[top].step = s;
            }
        }
    }

    int first = 1;
    for (int i = top; i >= 0; i--)
    {
        if (!first)
            printf(" ");
        first = 0;
        printf("%d-%d", reverseDir(stack[i].dir), stack[i].step);
    }
    printf("\n");

    return 0;
}