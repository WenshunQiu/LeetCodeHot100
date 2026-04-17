#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 2000

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Create a new tree node
TreeNode *createNode(int val)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Parse the input array and build tree using queue approach
TreeNode *buildTree(int *levelOrder, int size)
{
    if (size == 0 || levelOrder[0] == -10001)
        return NULL;

    TreeNode *root = createNode(levelOrder[0]);

    TreeNode *queue[MAX_NODES];
    int queueFront = 0, queueRear = 0;
    queue[queueRear++] = root;

    int i = 1;
    while (queueFront < queueRear && i < size)
    {
        TreeNode *node = queue[queueFront++];

        // Process left child
        if (i < size)
        {
            if (levelOrder[i] != -10001)
            {
                node->left = createNode(levelOrder[i]);
                queue[queueRear++] = node->left;
            }
            i++;
        }

        // Process right child
        if (i < size)
        {
            if (levelOrder[i] != -10001)
            {
                node->right = createNode(levelOrder[i]);
                queue[queueRear++] = node->right;
            }
            i++;
        }
    }

    return root;
}

// Flatten binary tree to linked list in-place (Morris-like approach, O(1) space)
void flatten(TreeNode *root)
{
    if (root == NULL)
        return;

    TreeNode *curr = root;
    while (curr != NULL)
    {
        if (curr->left != NULL)
        {
            // Find the rightmost node in the left subtree
            TreeNode *rightmost = curr->left;
            while (rightmost->right != NULL)
            {
                rightmost = rightmost->right;
            }

            // Rewire: rightmost's right points to curr's right
            rightmost->right = curr->right;

            // Move left subtree to right
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
}

// Output the flattened tree as [val, null, val, null, ...]
void outputFlattened(TreeNode *root)
{
    if (root == NULL)
    {
        printf("[]");
        return;
    }

    printf("[");
    TreeNode *curr = root;
    int first = 1;

    while (curr != NULL)
    {
        if (!first)
            printf(",");
        printf("%d", curr->val);

        // Only add null after each node except the last one
        if (curr->right != NULL)
        {
            printf(",null");
        }

        first = 0;
        curr = curr->right;
    }

    printf("]");
}

// Parse input string like "[1,2,5,3,4,null,6]"
int parseInput(const char *input, int *levelOrder)
{
    int size = 0;

    // Skip to '['
    while (*input && *input != '[')
        input++;
    if (*input == '[')
        input++;

    // Parse numbers and null
    while (*input && *input != ']' && size < MAX_NODES)
    {
        // Skip whitespace and commas
        while (*input && (*input == ' ' || *input == ','))
            input++;
        if (*input == ']' || *input == '\0')
            break;

        // Check for null
        if (strncmp(input, "null", 4) == 0)
        {
            levelOrder[size++] = -10001; // Sentinel for null
            input += 4;
        }
        else
        {
            // Parse number (including negative)
            int num = 0;
            int sign = 1;

            if (*input == '-')
            {
                sign = -1;
                input++;
            }

            while (*input >= '0' && *input <= '9')
            {
                num = num * 10 + (*input - '0');
                input++;
            }

            levelOrder[size++] = sign * num;
        }
    }

    return size;
}

int main()
{
    char input[10000];
    int levelOrder[MAX_NODES];

    // Read entire input line
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("[]");
        return 0;
    }

    // Remove trailing newline
    input[strcspn(input, "\n")] = '\0';

    int size = parseInput(input, levelOrder);

    TreeNode *root = buildTree(levelOrder, size);
    flatten(root);
    outputFlattened(root);
    printf("\n");

    return 0;
}
