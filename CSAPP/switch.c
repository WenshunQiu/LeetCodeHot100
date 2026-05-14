#include <stdio.h>
long swap_add(int *a, int *b)
{
    long x = *a;
    long y = *b;
    *a = y;
    *b = x;
    return x + y;
}
int main()
{
    int a = 1, b = 2;
    long sum = swap_add(&a, &b);
    printf("%ld\n", sum);
}