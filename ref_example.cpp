#include <iostream>
#include <functional>
 
void foo(int& a) {
    ++a;
}
 
void test_function(std::function<void(void)> fun) {
    fun();
}
 
int main() {
    int a = 1;
 
    std::cout << "a = " << a << "\n";
    test_function(std::bind(foo, a));   // 函数编程，绑定后直接使用了，绑定的是函数名＋参数
    std::cout << "a = " << a << "\n";
    test_function(std::bind(foo, std::ref(a)));
    std::cout << "a = " << a << "\n";
 
    return 0;
}