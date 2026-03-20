#include <iostream>
using namespace std;

struct linkdList
{
    int data;
    linkdList *next;
};

int main()
{
    // 输入数据
    int len;
    linkdList *head = NULL;
    linkdList *tail = NULL;
    cin >> len;
    head = new linkdList;
    cin >> head->data;
    tail = head;
    for (int i = 0; i < len - 1; i++)
    {
        linkdList *temp = new linkdList;
        cin >> temp->data;
        tail->next = temp;
        tail = temp;
        temp->next = nullptr;
    }
    // 头 尾

    // 调整数据
    // 找到最大的数据
    linkdList *p = head;
    linkdList *prep = nullptr;
    linkdList *max = head;
    linkdList *premax = nullptr;

    while (p != nullptr)
    {
        if (p->data >= max->data)
        {
            premax = prep;
            max = p;
        }
        prep = p;
        p = p->next;
    }
    // 最大 最大之前

    // 调换顺序
    if (max != tail)
    {
        if (max == head)
        {
            head = max->next;
        }
        else
        {
            premax->next = max->next;
        }

        tail->next = max;
        max->next = nullptr;
    }

    while (head != nullptr)
    {
        cout << head->data << endl;
        head = head->next;
    }
}
