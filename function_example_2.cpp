#include <iostream>
#include <functional>
using namespace std;

class Test{
public:
    int sum(int a , int b) {
        return a+b;
    }
};

int sum(int a, int b, int c)
{
    return a+b+c;
}

int add(int &a, int &b)
{
    a++;
    b++;
    cout << a << ", " << b << endl;
}

function<int(int, int)> Func1;  // 绑定成员函数，参数即成员函数参数
function<int(Test, int, int)> Func2;    // 绑定成员函数，参数首位为类名

int main()
{
    Test obj;

    // 1. using std::bind 绑定成员函数
    Func1 = std::bind(&Test::sum, obj, std::placeholders::_1, std::placeholders::_2);
    cout << "Func1 = " << Func1(1,2) << endl;

    // 2. Point member function 直接指向成员函数
    Func2 = &Test::sum;
    cout << "Func2 = " << Func2(obj, 1, 2) << endl;
    

    auto Func3 = std::bind(sum, 1, 2, 3);
    cout << "Func3 = " << Func3() << endl;


    int a = 1, b = 1;
    auto Func4 = std::bind(add, a, b);  // 对于预先绑定的参数，是通过值传递的
    Func4();    // 2, 2
    cout << a << ", " << b << endl; // 1, 1

    a = 1;
    b = 1;
    auto Func5 = std::bind(add, placeholders::_1, b);   // 对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的
    Func5(a);   // 2, 2
    cout << a << ", " << b << endl; // 2, 1

    return 0;
}


