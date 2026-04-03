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