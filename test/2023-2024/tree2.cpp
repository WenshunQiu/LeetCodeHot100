#include <stack>
#include <iostream>
using namespace std;

typedef struct BTNode
{
    char Data;
    struct BTNode *lchild;
    struct BTNode *rchild;
    int peeked = 0;
    BTNode(char data, BTNode *lchild, BTNode *rchild)
    {
        this->Data = data;
        this->lchild = lchild;
        this->rchild = rchild;
    }
} BTNode;

void makeTree(BTNode *&root)
{
    BTNode *r = new BTNode('K', nullptr, nullptr);
    r = new BTNode('J', nullptr, r);
    r = new BTNode('I', nullptr, r);
    r = new BTNode('H', r, nullptr);
    r = new BTNode('G', r, nullptr);
    r = new BTNode('D', r, nullptr);
    r = new BTNode('C', nullptr, r);
    BTNode *d = new BTNode('F', nullptr, nullptr);
    d = new BTNode('E', nullptr, d);
    r = new BTNode('B', d, r);
    r = new BTNode('A', r, nullptr);
    root = r;
}

void oncePrint(BTNode *node)
{
    if (node->peeked == 0)
    {
        printf("%c", node->Data);
        node->peeked = 1;
    }
}

void HTravserse(BTNode *root) // ans:EBFACIHJKGD。
{
    if (root == nullptr)
        return;

    stack<BTNode *> stk;
    stack<int> state;
    stack<int> inForest;

    stk.push(root);
    state.push(0);
    inForest.push(0);

    while (!stk.empty())
    {
        BTNode *cur = stk.top();
        int st = state.top();            // 回溯输出标记，用来标记是否第二次访问，入栈和出栈解耦
        int forestFlag = inForest.top(); // 右子树标记，即标记是否是森林的元素

        if (st == 0)
        {
            state.top() = 1;
            if (cur->lchild != nullptr)
            {
                stk.push(cur->lchild);
                state.push(0);
                inForest.push(0);
            }
            continue;
        }

        if (st == 1)
        {
            oncePrint(cur);
            state.top() = 2;

            BTNode *restForest = (cur->lchild == nullptr) ? nullptr : cur->lchild->rchild;
            if (restForest != nullptr)
            {
                stk.push(restForest);
                state.push(0);
                inForest.push(1);
            } //(6)   在遍历二叉树的过程中，遇到左子树为空，而右子树不空的结点，
            // 要同时输出该结点及其父结点（如连续输出E、B）。（5分）
            continue;
        }

        stk.pop();
        state.pop();
        inForest.pop();
        //(7)   在遍历二叉树的过程中，一旦对一个结点进行退栈操作，意味着要连续对一系列的结点进行退栈操作。
        // 条件包括右子树为空或者右子树已经处理完毕，或者左子树已经处理完毕且右子树为空。（5分）
        if (forestFlag == 1 && cur->rchild != nullptr)
        {
            stk.push(cur->rchild);
            state.push(0);
            inForest.push(1);
        }
    }
}

void freeTree(BTNode *root)
{
    if (root == nullptr)
        return;

    stack<BTNode *> stk;
    stack<BTNode *> out;
    stk.push(root);

    while (!stk.empty())
    {
        BTNode *cur = stk.top();
        stk.pop();
        out.push(cur);

        if (cur->lchild != nullptr)
            stk.push(cur->lchild);
        if (cur->rchild != nullptr)
            stk.push(cur->rchild);
    }

    while (!out.empty())
    {
        delete out.top();
        out.pop();
    }
}

int main()
{
    BTNode *root;
    makeTree(root);
    HTravserse(root);
    freeTree(root);
    return 0;
}
