#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;
void divide(string data)
{
    cout << "------------------" << data << "-----------------" << endl;
}
void divide()
{
    cout << "------------------" << "----" << "-----------------" << endl;
}
void fun(int p[100])
{
    cout << sizeof(p) << endl;
    // 作为参数传递的数组将退化为指针
}
void GetMemory(char *&p, int num)
{
    p = (char *)malloc(sizeof(char) * num);
}
void Test(void)
{
    char *str = NULL;
    GetMemory(str, 100); // str 仍然为 NULL
    if (str == nullptr)
    {
        cout << "str is null!!" << endl;
    }
    strcpy(str, "hello"); //  上面改为引用后不会出错
    cout << str << endl;
}

class Obj
{
private:
    int a = 0;

public:
    Obj();
    ~Obj();
};

Obj::Obj()
{
    cout << "obj is created" << endl;
}

Obj::~Obj()
{
    cout << "obj is cleaned" << endl;
}

int main()
{
    // 一个字节对应两个十六进制 A8
    // 相当于16*16 = 256个二进制
    // int a;
    // scanf("%d",&a);
    divide("一些数据大小");
    cout << "sizeof int:" << sizeof(int) << endl;
    cout << "sizeof char:" << sizeof(char) << endl;
    divide("临时变量不作引用，那就改不了");
    int t[100] = {0};
    fun(t);
    Test();
    divide("new和delete会自动执行构造和析构函数，malloc和free不会");
    Obj *obj = new Obj;
    delete obj;
    // Obj *obj = new Obj;
    //  好吧这里报错是因为重新声明了，虽然obj被del了，但是它也是被声明过了的，此时它还在栈中，但是它的指向应该是null了;
    if (obj == nullptr)
    {
        printf("obj is null");
    }
    char* p = "hello world";
    if (p != nullptr)
    {
        printf("p is malloced");
    }
    delete p;//发癫，这玩意del不掉的，第一这是全局变量，第二这是p指针，没有人知道它指向数组的大小
    if (p == nullptr)
    {
        printf("p is freed");
    }
}
