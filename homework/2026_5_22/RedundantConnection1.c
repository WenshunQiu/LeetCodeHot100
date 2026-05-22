#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define MAXLINE 200010

int parent[MAXN];

int findRoot(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findRoot(parent[x]);
    }
    return parent[x];
}

int main()
{
    char line[MAXLINE];
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 0;
    }
    int nums[2 * MAXN];
    int numCount = 0;
    int len = (int)strlen(line);

    for (int i = 0; i < len;)
    {
        if (isdigit((unsigned char)line[i]))
        {
            int value = 0;
            while (i < len && isdigit((unsigned char)line[i]))
            {
                value = value * 10 + (line[i] - '0');
                i++;
            }
            if (numCount < 2 * MAXN)
            {
                nums[numCount++] = value;
            }
        }
        else
        {
            i++;
        }
    } // 数据输入
    int edgeCount = numCount / 2;
    int ansA = 0;
    int ansB = 0;
    for (int i = 0; i < MAXN; i++)
    {
        parent[i] = i;
    }
    for (int i = 0; i < edgeCount; i++)
    {
        int a = nums[2 * i];
        int b = nums[2 * i + 1];
        int ra = findRoot(a);
        int rb = findRoot(b);
        if (ra == rb)
        {
            ansA = a;
            ansB = b;
        }
        else
        {
            parent[ra] = rb;
        }
    } // 寻根
    printf("[%d,%d]\n", ansA, ansB);
    return 0;
}
