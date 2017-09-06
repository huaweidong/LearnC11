#include <iostream>
#include <functional>

void f(int& a, int& b, const int & c)
{
    std::cout << "Inside funciont : " << a << " " << b << " " << c << std::endl;    // 1 12 13,虽然是int&a，但是函数编程中没用，还是得用std::ref修饰才行，另外，其值是bind时的值
    ++a;
    ++b;
}
 
int main() {
    int a = 1, b = 2, c = 3;
    std::function<void()> bound_f = std::bind(f, a, std::ref(b), std::cref(c));
 
    a = 11;
    b = 12;
    c = 13;

    std::cout << "Before funciont : " << a << " " << b << " " << c << std::endl;
    bound_f();
    std::cout << "After funciont : " << a << " " << b << " " << c << std::endl;
    return 0;
}