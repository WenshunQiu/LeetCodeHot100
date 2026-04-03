#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100000

int main(int argc, char const *argv[])
{
    int len;
    scanf("%d", &len);
    int poke[N];
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &poke[i]);
    }
    int deque[N];
    int place[14];
    memset(deque, 0, sizeof(deque));
    memset(place, -1, sizeof(place));
    int leftPointer = 0;
    int rightPointer = len;
    int pointer = 0;
    int out = 0;
    while (leftPointer < rightPointer)
    {
        if (place[poke[leftPointer]] != -1)
        {
            int where = place[poke[leftPointer]];
            for (int i = pointer - 1; i > where; i--)
            {
                poke[rightPointer++] = deque[i];
            }
            for (int i = where; i < pointer; i++)
            {
                place[deque[i]] = -1;
            }
            pointer = where;
            for (int i = 0; i < pointer; i++)
            {
                place[deque[i]] = i;
            }
        }
        else
        {
            place[poke[leftPointer]] = pointer;
            deque[pointer++] = poke[leftPointer];
        }
        leftPointer++;
        out++;
    }

    printf("%d\n", out);

    return 0;
}