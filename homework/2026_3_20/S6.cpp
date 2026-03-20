#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 单链表结点
struct Node
{
    int data;
    Node *next;
};

Node *createList(int m)
{
    Node *head = nullptr, *tail = nullptr;
    for (int i = 1; i <= m; i++)
    {
        Node *p = new Node();
        p->next = nullptr;
        p->data = i;

        if (head == nullptr)
        {
            head = tail = p;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }
    return head;
}

// 把普通单链表变成循环单链表，并返回尾指针
Node *makeCircle(Node *head)
{
    if (head == nullptr)
        return nullptr;
    Node *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = head;
    return tail;
}

Node *josephusRound(Node *head, int k)
{
    if (head == nullptr)
        return nullptr;

    // 先变成循环链表
    Node *tail = makeCircle(head);

    Node *newHead = nullptr, *newTail = nullptr;

    Node *pre = tail;
    Node *cur = head;

    while (cur != pre) // 圈中不止一个结点
    {
        for (int i = 1; i < k; i++)
        {
            pre = cur;
            cur = cur->next;
        }

        pre->next = cur->next;

        // 接到新队列末尾
        cur->next = nullptr;
        if (newHead == nullptr)
        {
            newHead = newTail = cur;
        }
        else
        {
            newTail->next = cur;
            newTail = cur;
        }

        cur = pre->next;
    }

    // 处理最后一个结点
    cur->next = nullptr;
    if (newHead == nullptr)
    {
        newHead = newTail = cur;
    }
    else
    {
        newTail->next = cur;
        newTail = cur;
    }

    return newHead;
}

// 输出链表
void printList(Node *head)
{
    Node *p = head;
    while (p != nullptr)
    {
        cout << setw(4) << p->data;
        p = p->next;
    }
    cout << endl;
}

int main()
{
    vector<int> nums;
    int x;

    while (cin >> x)
    {
        nums.push_back(x);
    }

    if (nums.empty())
        return 0;

    int m = nums[0];
    Node *head = createList(m);

    for (int i = 1; i < nums.size(); i++)
    {
        head = josephusRound(head, nums[i]);
    }

    printList(head);
    return 0;
}