#include <stdio.h>

#define MAXN 1000
int main()
{
    int n;
    scanf("%d", &n);

    int in[MAXN], out[MAXN], stack[MAXN];
    int top = -1;
    int j = 0;
    int popCount = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &in[i]);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &out[i]);
    }
    
    for (int i = 0; i < n; i++)
    {
        stack[++top] = in[i];

        while (top >= 0 && j < n && stack[top] == out[j])
        {
            top--;
            j++;
            popCount++;
        }
    }

    if (j == n)
    {
        printf("%d\n", popCount);
    }
    else
    {
        printf("0\n");
    }

    return 0;
}