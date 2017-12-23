#include <iostream>
#include <functional>
using namespace std;

// std::function可以绑定全局函数、类静态函数以及Lambda表达式等，但绑定成员函数时，须借助std::bind帮忙，或者传入*this指针。
// c++11中callable object 包括传统C函数，C++成员函数，函数对象（实现了（）运算符的类的实例），lambda表达式（特殊函数对象）共4种
function<int(int)> Functional;

// 普通函数
int TestFunc(int i) {
    return i;
}

// lambda表达式
auto lambda = [](int i)-> int { return i;};

// 仿函数（函数对象）
class Functor {
public:
    int operator()(int i) {
        return i;
    }
};

// 类成员函数
// 类静态函数
class Test {
public:
    int foo(int i){ return i;}
    static int staticFunc(int i) { return i;}
};

int main()
{
    Functional = TestFunc;
    cout << "普通函数" << Functional(1) << endl;

    Functional = lambda;
    cout << "lambda表达式" << Functional(2) << endl;

    Functor func;
    Functional = func;
    cout << "仿函数" << Functional(3) << endl;

    Test obj;
    Functional = bind(&Test::foo, obj, placeholders::_1);
    cout << "类成员函数" << Functional(4) << endl;

    Functional = Test::staticFunc;
    cout << "类静态函数" << Functional(5) << endl;

    return 0;

    /* output 
    普通函数1
lambda表达式2
仿函数3
类成员函数4
类静态函数5
*/

}


