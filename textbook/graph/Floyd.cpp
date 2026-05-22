#include "graph.hpp"
#include <iostream>
void Floyd(MatGraph g)
{
    int A[MAXV][MAXV];    // Floy操作图
    int path[MAXV][MAXV]; // 保存i到j最短路径中，j的前一个元素
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            A[i][j] = g.edges[i][j];
            if (i != j && g.edges[i][j] < INF)
            {
                path[i][j] = i;
            }
            else
            {
                path[i][j] = -1;
            }
        }
    } // 初始化Floyd操作图
    for (int k = 0; k < g.n; k++) // 选取一个中间元素
    {
        for (int i = 0; i < g.n; i++) // 插入到从i到j的路径中
        {
            for (int j = 0; j < g.n; j++)
            {
                if (A[i][j] > A[i][k] + A[k][j]) // 更新长度
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    Dispath(g, A, path);
}

void Dispath(MatGraph g, int A[][MAXV], int path[][MAXV])
{
    int s, k;
    int apath[MAXV], d;
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            if (A[i][j] != INF && i != j)
            {
                printf("从%d到%d的路径为:", i, j);
                k = path[i][j];
                d = 0;
                apath[d] = j; // 一条路径，相当于栈。
                while (k != i)
                {
                    d++;
                    apath[d] = k;
                    k = path[i][k];
                }
                d++;
                apath[d] = i; // 把头放进去
                printf("%d", apath[d]);
                for (s = d - 1; s >= 0; s--) // 题外话：这个是不是可以看作是一种左闭右开原则呢
                {
                    printf(",%d", apath[s]);
                }
                printf("\t路径长度为:%d\n", A[i][j]);
            }
        }
    }
}