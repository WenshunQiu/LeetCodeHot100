#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main()//这样写会被大四的
{
    string s;
    getline(cin, s);
    int pos = s.find(" = ");
    if (pos == string::npos)
    {
        return 0;
    }

    string a = s.substr(pos + 3);
    cout << a << endl;
}