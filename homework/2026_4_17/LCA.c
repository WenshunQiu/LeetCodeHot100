#include <stdio.h>
#include <string.h>

#define MAXN 10005

int parent[MAXN];
int hasParent[MAXN];
int visited[MAXN];

int main() {
    FILE *fp = fopen("in.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return 0;
    }

    int n;
    fscanf(fp, "%d", &n);

    memset(parent, 0, sizeof(parent));
    memset(hasParent, 0, sizeof(hasParent));
    memset(visited, 0, sizeof(visited));

    // 读边
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        fscanf(fp, "%d%d", &u, &v);
        parent[v] = u;
        hasParent[v] = 1;
    }

    int x, y;
    fscanf(fp, "%d%d", &x, &y);

    fclose(fp);

    // 标记 x 的祖先
    int t = x;
    while (t != 0) {
        visited[t] = 1;
        t = parent[t];
    }

    // 找 y 的最近公共祖先
    t = y;
    while (t != 0) {
        if (visited[t]) {
            printf("%d\n", t);
            break;
        }
        t = parent[t];
    }

    return 0;
}