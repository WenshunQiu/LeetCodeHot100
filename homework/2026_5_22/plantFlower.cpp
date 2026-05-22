#include <cstdio>
#include <cstdlib>

#define MAXV 10005

typedef struct ANode
{
    int adjvex;
    struct ANode *nextarc;
} ArcNode;

typedef struct VNode
{
    ArcNode *firstarc;
} VNode;

typedef struct
{
    VNode adjlist[MAXV];
    int n, e;
} AdjGraph;

AdjGraph *CreateAG()
{
    AdjGraph *AG = (AdjGraph *)malloc(sizeof(AdjGraph));
    if (AG == nullptr)
    {
        return nullptr;
    }

    int n, e;
    if (scanf("%d %d", &n, &e) != 2)
    {
        free(AG);
        return nullptr;
    }

    AG->n = n;
    AG->e = e;

    for (int i = 1; i <= n; i++)
    {
        AG->adjlist[i].firstarc = nullptr;
    }

    for (int i = 0; i < e; i++)
    {
        int eA, eB;
        scanf("%d %d", &eA, &eB);

        ArcNode *ANa = (ArcNode *)malloc(sizeof(ArcNode));
        ArcNode *ANb = (ArcNode *)malloc(sizeof(ArcNode));

        ANa->adjvex = eB;
        ANa->nextarc = AG->adjlist[eA].firstarc;
        AG->adjlist[eA].firstarc = ANa;

        ANb->adjvex = eA;
        ANb->nextarc = AG->adjlist[eB].firstarc;
        AG->adjlist[eB].firstarc = ANb;
    }

    return AG;
}

void plantFlowers(AdjGraph *AG)
{
    int planted[MAXV] = {0};

    for (int i = 1; i <= AG->n; i++)
    {
        int used[5] = {0};
        ArcNode *p = AG->adjlist[i].firstarc;

        while (p != nullptr)
        {
            int c = planted[p->adjvex];
            if (c >= 1 && c <= 4)
            {
                used[c] = 1;
            }
            p = p->nextarc;
        }

        for (int color = 1; color <= 4; color++)
        {
            if (!used[color])
            {
                planted[i] = color;
                break;
            }
        }
    }

    for (int i = 1; i <= AG->n; i++)
    {
        if (i > 1)
        {
            printf(" ");
        }
        printf("%d", planted[i]);
    }
    printf("\n");
}

int main()
{
    AdjGraph *AG = CreateAG();
    if (AG == nullptr)
    {
        return 0;
    }

    plantFlowers(AG);
    return 0;
}
