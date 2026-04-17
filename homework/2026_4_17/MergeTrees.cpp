#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct
{
    char **data;
    int size;
    int capacity;
} StringVector;

StringVector *createStringVector()
{
    StringVector *vec = (StringVector *)malloc(sizeof(StringVector));
    vec->capacity = 100;
    vec->size = 0;
    vec->data = (char **)malloc(sizeof(char *) * vec->capacity);
    return vec;
}

void pushString(StringVector *vec, const char *str)
{
    if (vec->size >= vec->capacity)
    {
        vec->capacity *= 2;
        vec->data = (char **)realloc(vec->data, sizeof(char *) * vec->capacity);
    }
    vec->data[vec->size] = (char *)malloc(strlen(str) + 1);
    strcpy(vec->data[vec->size], str);
    vec->size++;
}

void freeStringVector(StringVector *vec)
{
    for (int i = 0; i < vec->size; i++)
    {
        free(vec->data[i]);
    }
    free(vec->data);
    free(vec);
}

char *trim(char *str)
{
    char *end;
    while (*str == ' ')
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ')
        end--;
    *(end + 1) = '\0';
    return str;
}

void parseInput(const char *line, StringVector *result)
{
    char *copy = (char *)malloc(strlen(line) + 1);
    strcpy(copy, line);

    // 去掉方括号
    char *start = copy + 1;
    char *end = strrchr(copy, ']');
    if (end)
        *end = '\0';

    char *token = strtok(start, ",");
    while (token != NULL)
    {
        char *trimmed = trim(token);
        pushString(result, trimmed);
        token = strtok(NULL, ",");
    }

    free(copy);
}

TreeNode *buildTree(StringVector *nodes, int index)
{
    if (index >= nodes->size)
    {
        return NULL;
    }
    if (strcmp(nodes->data[index], "null") == 0 || strlen(nodes->data[index]) == 0)
    {
        return NULL;
    }

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = atoi(nodes->data[index]);
    root->left = buildTree(nodes, 2 * index + 1);
    root->right = buildTree(nodes, 2 * index + 2);
    return root;
}

TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
{
    if (t1 == NULL)
    {
        return t2;
    }
    if (t2 == NULL)
    {
        return t1;
    }

    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);

    return t1;
}

typedef struct
{
    TreeNode **data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue *createQueue(int capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->data = (TreeNode **)malloc(sizeof(TreeNode *) * capacity);
    return q;
}

void enqueue(Queue *q, TreeNode *node)
{
    q->rear++;
    q->data[q->rear] = node;
}

TreeNode *dequeue(Queue *q)
{
    return q->data[q->front++];
}

int isQueueEmpty(Queue *q)
{
    return q->front > q->rear;
}

void freeQueue(Queue *q)
{
    free(q->data);
    free(q);
}

char *levelOrderToString(TreeNode *root)
{
    if (root == NULL)
    {
        char *result = (char *)malloc(3);
        strcpy(result, "[]");
        return result;
    }

    StringVector *result = createStringVector();
    Queue *q = createQueue(2000);

    enqueue(q, root);

    while (!isQueueEmpty(q))
    {
        TreeNode *node = dequeue(q);

        if (node == NULL)
        {
            pushString(result, "null");
        }
        else
        {
            char val[20];
            sprintf(val, "%d", node->val);
            pushString(result, val);
            enqueue(q, node->left);
            enqueue(q, node->right);
        }
    }

    // 去掉末尾的 null
    while (result->size > 0 && strcmp(result->data[result->size - 1], "null") == 0)
    {
        free(result->data[result->size - 1]);
        result->size--;
    }

    // 构建输出字符串
    int totalLen = 2; // [ and ]
    for (int i = 0; i < result->size; i++)
    {
        totalLen += strlen(result->data[i]);
        if (i > 0)
            totalLen += 1; // comma
    }

    char *output = (char *)malloc(totalLen + 1);
    strcpy(output, "[");
    for (int i = 0; i < result->size; i++)
    {
        if (i > 0)
            strcat(output, ",");
        strcat(output, result->data[i]);
    }
    strcat(output, "]");

    freeQueue(q);
    freeStringVector(result);

    return output;
}

void freeTree(TreeNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    char line1[10000], line2[10000];
    fgets(line1, sizeof(line1), stdin);
    fgets(line2, sizeof(line2), stdin);

    // 去掉换行符
    line1[strcspn(line1, "\n")] = '\0';
    line2[strcspn(line2, "\n")] = '\0';

    StringVector *nodes1 = createStringVector();
    StringVector *nodes2 = createStringVector();

    parseInput(line1, nodes1);
    parseInput(line2, nodes2);

    TreeNode *root1 = buildTree(nodes1, 0);
    TreeNode *root2 = buildTree(nodes2, 0);

    TreeNode *merged = mergeTrees(root1, root2);

    char *output = levelOrderToString(merged);
    printf("%s\n", output);

    free(output);
    freeTree(merged);
    freeStringVector(nodes1);
    freeStringVector(nodes2);

    return 0;
}
