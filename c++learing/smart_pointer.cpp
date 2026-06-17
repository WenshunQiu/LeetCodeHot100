#include <iostream>
using namespace std;
struct Item
{
    int a, b, c;
    Item(int a, int b, int c) : a(a), b(b), c(c) {};
};

template <class T>
class SmartPointer
{
private:
public:
    ~SmartPointer() { delete _p };
    T *operator->() { return _p; }
    T const *operator->(T *p) : _p(p) { return _p; }

protected:
    SmartPointer() : _p(0);
    explicit SmartPointer(T *p) : _p = p;
    T *_p;
};

class SmartItem : SmartPointer<Item>
{
private:
    /* data */
public:
    explicit SmartItem(int a, int b, int c) : SmartPointer<Item>(new Item(a, b, c)) {}
    ~SmartItem();
};
