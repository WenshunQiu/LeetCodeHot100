#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define MAXLINE 20050

int parent[MAXN];

int findRoot(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findRoot(parent[x]);
    }
    return parent[x];
}

int main(void)
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
    }

    int edgeCount = numCount / 2;
    int answerA = 0, answerB = 0;

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
            answerA = a;
            answerB = b;
        }
        else
        {
            parent[ra] = rb;
        }
    }

    printf("[%d,%d]\n", answerA, answerB);
    return 0;
}
