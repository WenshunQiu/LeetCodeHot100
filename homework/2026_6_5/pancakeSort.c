#include <stdio.h>
#include <string.h>
#define MAX 105
// 找到最大的，在最大处反转
int findMax(int nums[], int n)
{
    int index = 0;
    int max = -1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
            index = i;
        }
    }
    return index;
}
void pancake(int nums[], int index)
{
    index--;
    for (int i = 0; i < (index + 1) / 2; i++)
    {
        int temp = nums[i];
        nums[i] = nums[index - i];
        nums[index - i] = temp;
    }
}
int lines[MAX];
int linesNums = 0;
void pancakeSort(int nums[], int len)
{
    int inorderedNums = len;
    memset(lines, 0, sizeof(lines));
    while (inorderedNums != 0)
    {
        int maxIndex = 0;
        maxIndex = findMax(nums, inorderedNums);
        // if (maxIndex == 0)
        // {
        //     continue;
        // }
        // pancake(nums, maxIndex + 1);
        // pancake(nums, inorderedNums);
        // lines[linesNums++] = maxIndex + 1;
        // lines[linesNums++] = inorderedNums;
        if (maxIndex != inorderedNums - 1)
        {
            if (maxIndex != 0)
            {
                pancake(nums, maxIndex + 1);
                lines[linesNums++] = maxIndex + 1;
            }

            pancake(nums, inorderedNums);
            lines[linesNums++] = inorderedNums;
        }
        inorderedNums--;
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
        if (c <= '9' && c >= '0')
        {
            int temp = 0;
            while (c <= '9' && c >= '0')
            {
                temp = temp * 10 + (c - '0');
                c = getchar();
            }
            nums[numsp++] = temp;
        }
        c = getchar();
    }
    pancakeSort(nums, numsp);
    printf("[");
    if (linesNums == 0)
    {
        printf("]");
    }

    for (int i = 0; i < linesNums; i++)
    {
        printf("%d", lines[i]);
        if (i == linesNums - 1)
        {
            printf("]");
        }
        else
        {
            printf(",");
        }
    }
}