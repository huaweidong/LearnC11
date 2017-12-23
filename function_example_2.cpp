#include <iostream>
#include <functional>
using namespace std;

class Test{
public:
    int sum(int a , int b) {
        return a+b;
    }
};

function<int(int, int)> Func1;  // 绑定成员函数，参数即成员函数参数
function<int(Test, int, int)> Func2;    // 绑定成员函数，参数首位为类名

int main()
{
    Test obj;

    // 1. using std::bind
    Func1 = std::bind(&Test::sum, obj, std::placeholders::_1, std::placeholders::_2);
    cout << "Func1 = " << Func1(1,2) << endl;

    // 2. Point member function
    Func2 = &Test::sum;
    cout << "Func2 = " << Func2(obj, 1, 2) << endl;
    return 0;
}


