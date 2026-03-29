#include <stdio.h>
#include <string.h>

#define MAX_FUNC 105
#define MAX_NAME 25
#define MAX_STACK 205
typedef struct
{
    char name[MAX_NAME];
    char called[MAX_FUNC][MAX_NAME];
    int count;
    int exist;
} Func;

Func funcList[MAX_FUNC];
int funcNum = 0;

char stack[MAX_STACK][MAX_NAME];
int top = -1;

int findFunc(char *name)
{
    for (int i = 0; i < funcNum; i++)
    {
        if (strcmp(funcList[i].name, name) == 0)
        {
            return i; // 如果存在，就返回索引
        }
    }
    // 如果不存在，就创建一个
    strcpy(funcList[funcNum].name, name);
    funcList[funcNum].count = 0;
    funcList[funcNum].exist = 0;
    return funcNum++;
}

int isCalled(Func *f, char *name)
{
    for (int i = 0; i < f->count; i++)
    {
        if (strcmp(f->called[i], name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void addCall(char *parent, char *child)
{
    int pIdx = findFunc(parent);
    if (isCalled(&funcList[pIdx], child))
        return;

    strcpy(funcList[pIdx].called[funcList[pIdx].count], child);
    funcList[pIdx].count++;
}

int main()
{
    int op;
    char name[MAX_NAME];

    while (1)
    {
        scanf("%d", &op);

        if (op == 5)
        {
            scanf("%s", name);
            if (top != -1)
            {
                addCall(stack[top], name);
            }
            strcpy(stack[++top], name);
            findFunc(name);
        }
        else if (op == 0)
        {
            top--;
            if (top == -1)
                break;
        }
    }

    for (int i = 0; i < funcNum; i++)
    {
        Func f = funcList[i];
        if (f.count == 0)
            continue;

        printf("%s:", f.name);
        for (int j = 0; j < f.count; j++)
        {
            if (j > 0)
                printf(";");
            printf("%s", f.called[j]);
        }
        printf("\n");
    }

    return 0;
}