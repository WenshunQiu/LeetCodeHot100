#include <iostream>
using namespace std;
class A
{
public:
    A(int a1 = 0, int a2 = 0)
        : _a1(a1), _a2(a2)
    {
        cout << "A(int a1 = 0, int a2 = 0)" << endl;
    }

    A(const A &aa)
        : _a1(aa._a1)
    {
        cout << "A(const A& aa)" << endl;
    }

    A &operator=(const A &aa)
    {
        cout << "A& operator=(const A& aa)" << endl;
        if (this != &aa)
        {
            _a1 = aa._a1;
        }
        return *this;
    }

    ~A()
    {
        // delete _ptr;
        cout << "~A()" << endl;
    }

    void Print()
    {
        cout << "A::Print->" << _a1 << endl;
    }

    A &operator++()
    {
        _a1 += 100;

        return *this;
    }

private:
    int _a1 = 1;
    int _a2 = 1;
};
class B
{
private:
    int _b1 = 2;
    int _b2 = 2;
};
int main()
{

    B *p2 = new B[10];
    delete p2;
    A *p3 = new A[10];
    delete p3;

    return 0;
}