#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int val)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

int isNullToken(const char *s)
{
    return strcmp(s, "null") == 0 || strcmp(s, "NULL") == 0 ||
           strcmp(s, "N") == 0 || strcmp(s, "#") == 0;
}

void normalizeInput(char *line)
{
    for (int i = 0; line[i]; i++)
    {
        if (line[i] == '[' || line[i] == ']' || line[i] == ',')
        {
            line[i] = ' ';
        }
    }
}

TreeNode *buildTreeFromLevelOrder(char tokens[][20], int count)
{
    if (count == 0 || isNullToken(tokens[0]))
        return NULL;

    TreeNode *root = createNode(atoi(tokens[0]));
    TreeNode *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int i = 1;
    while (front < rear && i < count)
    {
        TreeNode *cur = queue[front++];

        // 左孩子
        if (i < count && !isNullToken(tokens[i]))
        {
            cur->left = createNode(atoi(tokens[i]));
            queue[rear++] = cur->left;
        }
        i++;

        // 右孩子
        if (i < count && !isNullToken(tokens[i]))
        {
            cur->right = createNode(atoi(tokens[i]));
            queue[rear++] = cur->right;
        }
        i++;
    }

    return root;
}

// 前序遍历
void preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    printf("%d", root->val);
    if (root->left != NULL || root->right != NULL)
        printf(" ");
    else
        return;

    // 为了控制空格格式，单独处理
    if (root->left)
    {
        preorder(root->left);
        if (root->right)
            printf(" ");
    }
    if (root->right)
    {
        preorder(root->right);
    }
}

int firstPrint = 1;
void preorderPrint(TreeNode *root)
{
    if (root == NULL)
        return;
    if (!firstPrint)
        printf(" ");
    printf("%d", root->val);
    firstPrint = 0;
    preorderPrint(root->left);
    preorderPrint(root->right);
}

// 翻转二叉树
void invertTree(TreeNode *root)
{
    if (root == NULL)
        return;
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invertTree(root->left);
    invertTree(root->right);
}

int main()
{
    char line[2000];
    char tokens[1000][20];
    int count = 0;

    // 读取一整行输入
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        return 0;
    }

    normalizeInput(line);

    // 分割 token
    char *p = strtok(line, " \n\r\t");
    while (p != NULL)
    {
        strcpy(tokens[count++], p);
        p = strtok(NULL, " \n\r\t");
    }

    TreeNode *root = buildTreeFromLevelOrder(tokens, count);

    printf("原树的前序遍历: ");
    firstPrint = 1;
    preorderPrint(root);
    printf("\n");

    invertTree(root);

    printf("翻转后的前序遍历: ");
    firstPrint = 1;
    preorderPrint(root);
    printf("\n");

    return 0;
}
