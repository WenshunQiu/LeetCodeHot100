#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

// 栈帧结构体：存储递归参数和状态

typedef struct
{

    int n; // 当前阶乘参数

    char status[20]; // 状态描述（如"待计算n*?"）

} StackFrame;

// 顺序栈定义

typedef struct
{

    StackFrame data[MAX_SIZE];

    int top;

} SeqStack;

// 初始化栈

void initStack(SeqStack *s)
{

    s->top = -1;
}

// 判空

bool isEmpty(SeqStack *s)
{

    return s->top == -1;
}

// 判满

bool isFull(SeqStack *s)
{

    return s->top >= MAX_SIZE - 1;
}

// 入栈（需补充状态管理逻辑）

void push(SeqStack *s, int n, const char *status)
{

    if (isFull(s))
    {

        printf("Stack overflow!\n");

        return;
    }

    s->data[++s->top].n = n;

    snprintf(s->data[s->top].status, 20, "%s", status); // 将字符串 status 按格式 %s 写入目标字符数组 s->data[s->top].status 中, 用于防止缓冲区溢出

    printf("[Push] n=%d, Status: %s\n", n, status);
}

// 出栈（需补充计算逻辑）

StackFrame pop(SeqStack *s)
{

    if (isEmpty(s))
    {

        printf("Stack empty!\n");

        return (StackFrame){-1, ""};
    }

    StackFrame frame = s->data[s->top--];

    printf("[Pop] n=%d, Status: %s\n", frame.n, frame.status);

    return frame;
}

// 阶乘计算函数（需用栈模拟递归）

int factorial(int n)
{

    SeqStack s;

    initStack(&s);

    int result = 1;

    push(&s, n, "n*?");
    while (!isEmpty(&s))
    {
        StackFrame frame = pop(&s);
        if (strcmp(frame.status, "n*?") == 0)
        {
            if (frame.n == 1 || frame.n == 0)
            {
                result = 1;
            }
            else
            {
                push(&s, frame.n, "Calculate product");
                push(&s, frame.n - 1, "n*?");
            }
        }
        else if (strcmp(frame.status, "Calculate product") == 0)
        {
            result *= frame.n;
        }
    }

    // 补充完整w

    // 模拟递归压栈过程（补充代码）

    // 提示：压栈时需保存参数n和状态

    // （其中，状态"n*?"表示递推过程中因(n-1)!未知，n*(n-1)!为待计算状态，状态"Calculate product"为回归过程计算乘积状态）

    // 模拟递归出栈过程（补充代码）

    // 提示：根据状态计算乘积并更新result

    // 初始压栈：n 和状态"待计算n*?"

    return result;
}

int main()
{

    int n;

    scanf("%d", &n);

    printf("Final result: %d\n", factorial(n));

    return 0;
}