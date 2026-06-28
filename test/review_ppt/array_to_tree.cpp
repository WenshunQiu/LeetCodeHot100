#include <iostream>
#include <queue>
#include "textbook/tree/tree.hpp"
using namespace std;

// template <class T> class BTNode
// {
// private:
//     T element;
//     BTNode* lchild;
//     BTNode* rchild;
// public:
//     BTNode(){
//         lchild = rchild = nullptr;
//     };
//     ~BTNode();
// };

void makeTree(BTNode *&root, char a[], int n) // 至于这里为什么不用从1开始是因为你下面的数组怎么是从0开始的啊
{
    if (a == nullptr || n <= 0)
    {
        root = nullptr;
        return;
    }
    int i = 0;
    root = new BTNode(a[0]);
    queue<BTNode *> q;
    q.push(root);
    while (!q.empty() && i <= n)
    {
        BTNode *tmp = q.front();
        q.pop();
        if (i * 2 + 1 < n)
        {
            tmp->lchild = new BTNode(a[i * 2 + 1]);
            // tmp->lchild = &BTNode(a[i * 2 + 1]);
            /*这样写是非法的，右边在栈上创建了临时对象(它(BTNode(a[i * 2 + 1]))的生命周期是到分号结束！不是大括号！)，
            然后取的是栈的地址，会导致野指针，
            也就是说，这句话执行完后，tmp->lchild就是野指针了！
            如果是BTNode p = BTNode('a')，
            它的执行流程是：
            1.构建栈临时对象(BTNode('a'))(生命周期到;结束)
            2.拷贝构造p
            3.遇到分号，销毁临时对象(BTNode('a'))
            有些编译器会优化为 BTNode p('a')，就直接构造了对象，没有创建，拷贝和销毁临时对象
             */
            q.push(tmp->lchild);
        }
        if (i * 2 + 2 < n)
        {
            tmp->rchild = new BTNode(a[i * 2 + 2]);
            q.push(tmp->rchild);
        }
        i++;
    }
}
void printTreeInorder(BTNode *root)
{
    if (root != nullptr)
    {
        printTreeInorder(root->lchild);
        printf("%c", root->data);
        printTreeInorder(root->rchild);
    }
}
int main()
{
    char a[] = {'a', 'b', 'c', 'd', 'e'};
    BTNode *root;
    makeTree(root, a, 5);
    printTreeInorder(root);
}
