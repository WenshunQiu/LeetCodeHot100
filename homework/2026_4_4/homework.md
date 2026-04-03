## 理论作业

### 9.

(1) AD

(2) 

```cpp
#include <iostream>
#include <cstring>
#define M 1000000007
using namespace std;
int islegal(char op[], int n)
{
    int i = 0;
    int hasNum = 0;
    while (i < n)
    {
        switch (op[i])
        {
        case 'I':
            hasNum++;
            break;
        case 'O':
            if (!hasNum)
            {
                return 0;
            }
            hasNum--;
            break;
        default:
            break;
        }
        i++;
    }
    if (hasNum)
    {
        return 0;
    }
    return 1;
}
// AD合法

```

### 12

```c
#define N 10//容量为n
typedef struct
{
    int data[N];
    int front;
    int rear;
    int count;
} Queue;

void ReverseQueue(Queue *Q)
{
    int stk[N];
    int top = -1;

    while (Q->count > 0)
    {
        int x = Q->data[Q->front];
        Q->front = (Q->front + 1) % N;
        Q->count--;
        stk[++top] = x;
    }

    while (top != -1)
    {
        int x = stk[top--];
        Q->data[Q->rear] = x;
        Q->rear = (Q->rear + 1) % N;
        Q->count++;
    }
}
```
