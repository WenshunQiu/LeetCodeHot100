#include <stdio.h>

#define MAXN 1005

typedef struct
{
    int dir;
    int step;
} Node;

Node stack[MAXN];
int top = -1;

int opposite(int a, int b)
{
    return (a == 1 && b == 2) || (a == 2 && b == 1) ||
           (a == 3 && b == 4) || (a == 4 && b == 3);
}

int reverse_dir(int dir)
{
    if (dir == 1)
        return 2;
    if (dir == 2)
        return 1;
    if (dir == 3)
        return 4;
    return 3; // dir == 4
}

int main()
{
    int dir, step;

    while (1)
    {
        scanf("%d-%d", &dir, &step);
        if (dir == 0 && step == 0)
            break;

        int curDir = dir;
        int curStep = step;

        while (curStep > 0)
        {
            if (top >= 0 && opposite(curDir, stack[top].dir))
            { // 栈里面存储读入的每一步，在接收下一个数据的时候，处理上面的数据，如果可以抵消，则抵消掉
                // 栈适合在处理数据相邻相关的问题。
                if (curStep < stack[top].step)
                {
                    stack[top].step -= curStep;
                    curStep = 0;
                }
                else if (curStep == stack[top].step)
                {
                    top--;
                    curStep = 0;
                }
                else
                {
                    curStep -= stack[top].step;
                    top--;
                }
            }
            else
            {
                stack[++top].dir = curDir;
                stack[top].step = curStep;
                curStep = 0;
            }
        }
    }

    // 反向输出，并合并相邻同方向
    Node ans[MAXN];
    int cnt = 0;

    for (int i = top; i >= 0; i--)
    {
        int rd = reverse_dir(stack[i].dir);
        int rs = stack[i].step;

        if (cnt > 0 && ans[cnt - 1].dir == rd)
        {
            ans[cnt - 1].step += rs; // 合并相邻同方向
        }
        else // 如果方向不同则放入答案栈
        {
            ans[cnt].dir = rd;
            ans[cnt].step = rs;
            cnt++;
        }
    }

    for (int i = 0; i < cnt; i++) // 输出
    {
        printf("%d-%d", ans[i].dir, ans[i].step);
        if (i < cnt - 1)
            printf(" ");
    }
    printf("\n");

    return 0;
}