#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int people, ayy;
    cin >> people >> ayy;
    int chuangkou[ayy] = {0};
    int time[people] = {0};
    for (int i = 0; i < people; i++)
    {
        cin >> time[i];
    }
    sort(time, time + people);
    int total = 0;
    for (int i = 0; i < people; i++)
    {
        int pp = time[i];
        sort(chuangkou, chuangkou + ayy);
        total += chuangkou[0];
        chuangkou[0] += pp;
    }
    printf("%d", total); // 这个是nmd等待时间【不包括最后一个人的打饭时间】，不是总的打完饭的时间。
}