#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct cargo
{
    char destination[100];
    int lenth;
    int code;
} cargo;
typedef struct node
{
    char destination[100];
    int lenth;
} node;
int findLenth(int n, node *nodes, char *destination)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(nodes[i].destination, destination) == 0)
        {
            return nodes[i].lenth;
        }
    }
    return -1;
}

typedef struct stack
{
    int top;
    cargo cargo[100];
} stack;
stack *createStack()
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->top = -1;
    return stack;
}
void push(stack *stack, cargo cargo)
{
    stack->top++;
    stack->cargo[stack->top] = cargo;
}
cargo pop(stack *stack)
{
    stack->top--;
    return stack->cargo[stack->top + 1];
}
int findMaxIndex(stack *stack)
{
    int maxIndex = 0;
    for (int i = 0; i <= stack->top; i++)
    {
        if (stack->cargo[i].lenth >= stack->cargo[maxIndex].lenth)
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}
void transfer(stack *A, stack *B, int num)
{
    //printf("开始迁移\n");
    for (int i = 0; i < num; i++)
    {
        cargo tmpCargo = pop(A);
        push(B, tmpCargo);
        //printf("已迁移: %d\n", tmpCargo.code);
    }
    //printf("成功迁移: %d 个\n", num);
}

int main()
{
    int n;
    scanf("%d", &n);
    node nodes[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", &nodes[i].destination);
        scanf("%d", &nodes[i].lenth);
    }
    int nn;
    scanf("%d", &nn);
    stack *v5v5 = createStack();
    for (int i = 0; i < nn; i++)
    {
        cargo tmpCargo;
        scanf("%s", &tmpCargo.destination);
        tmpCargo.lenth = findLenth(n, nodes, tmpCargo.destination);
        scanf("%d", &tmpCargo.code);
        push(v5v5, tmpCargo);
    }
    //----------------------数据输入

    stack *B = createStack();
    stack *C = createStack();
    int countBPush = 0;

    // 先把v5v5的东西移到B中
    while (v5v5->top != -1)
    {
        cargo tmpCargo = pop(v5v5);
        push(B, tmpCargo);
        countBPush += 1;
    }
    while (v5v5->top != nn - 1)
    {
        // 要找到B中距离最大的并且是靠近栈顶的
        int maxIndex = findMaxIndex(B);
        //printf("找到B中最大的: %d\n", maxIndex);
        int transferNum = B->top - maxIndex + 1;
        //printf("需要移动: %d 个车厢\n", transferNum);
        // 移动到v5v5中
        transfer(B, v5v5, transferNum);
        // 需要判断是否有未编组的车厢
        // 这里只要判断transferNum是否为1
        if (transferNum == 1)
        {
            //printf("只移动一个车厢，满足条件");
            continue;
        }
        else
        {
            // 否则需要最前面的到C中
            cargo tmpCargo = pop(v5v5);
            push(C, tmpCargo);
            //printf("C中添加车厢: %d\n", tmpCargo.code);
            // 然后把未迁移的移动到B中
            //printf("移动剩余车厢到B中: %d\n", transferNum - 1);
            transfer(v5v5, B, transferNum - 1);
            countBPush += transferNum - 1;
            // 接着把C中的迁移到v5v5中
            //printf("C中移到v5v5中: %d\n", tmpCargo.code);
            transfer(C, v5v5, 1);
        }
    }
    //printf("最终结果:\n");
    for (int i = 0; i < nn; i++)
    {
        
        printf("%04d ", v5v5->cargo[i].code);
    }
    printf("\n%d", countBPush);
}
//当年轻一代开始用ai的时候，老一代还在坚持手搓代码