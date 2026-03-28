#include <stdio.h>
#include <string.h>

typedef struct Node
{
    int x, y;
    int direction;
} Node;

int main()
{
    int row, col;
    scanf("%d %d", &row, &col);
    
    int arr[row + 2][col + 2];
    int visited[row + 2][col + 2];
    memset(visited, 0, sizeof(visited));

    for (int i = 1; i <= row; i++)
    {
        char line[105];
        scanf("%s", line);
        for (int j = 1; j <= col; j++)
        {
            arr[i][j] = line[j-1] - '0';
        }
    }

    int dx[5] = {0, 0, 1, 0, -1};
    int dy[5] = {0, 1, 0, -1, 0};
    
    Node stack[1000];
    int top = -1;

    stack[++top] = (Node){1, 1, 0};
    visited[1][1] = 1;

    if (arr[1][1] == 1 || arr[row][col] == 1)
    {
        return 0;
    }

    while (top >= 0)
    {
        Node cur = stack[top];
        int x = cur.x;
        int y = cur.y;

        if (x == row && y == col)
        {
            stack[top].direction = 0;
            for (int i = 0; i <= top; i++)
            {
                printf("(%d,%d,%d)", stack[i].x, stack[i].y, stack[i].direction);
            }
            return 0;
        }

        int find = 0;
        for (int d = cur.direction + 1; d <= 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 1 && nx <= row && ny >= 1 && ny <= col 
                && arr[nx][ny] == 0 && visited[nx][ny] == 0)
            {
                stack[top].direction = d;
                stack[++top] = (Node){nx, ny, 0};
                visited[nx][ny] = 1;
                find = 1;
                break;
            }
        }

        if (!find)
        {
            top--;
        }
    }
    return 0;
}