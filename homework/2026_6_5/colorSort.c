#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 300
void insertSort(int R[], int n)
{
    int temp;
    int j;
    for (int i = 1; i < n; i++)
    {
        if (R[i] < R[i - 1])
        {
            temp = R[i];
            j = i - 1;
            do
            {
                R[j + 1] = R[j];
                j--;
            } while (j >= 0 && R[j] > temp);
            R[j + 1] = temp;
        }
    }
}
int main()
{
    int c;
    c = getchar();
    int nums[MAX];
    int numsp = 0;
    memset(nums, 0, sizeof(nums));
    while (c != EOF)
    {
        if (c <= '2' && c >= '0')
        {
            nums[numsp++] = c - '0';
        }
        c = getchar();
    }
    insertSort(nums, numsp);
    printf("[");
    for (int i = 0; i < numsp; i++)
    {
        printf("%d", nums[i]);
        if (i == numsp - 1)
        {
            printf("]");
        }
        else
        {
            printf(",");
        }
    }
}
