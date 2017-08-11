// example for thread::joinable
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
void mythread() 
{
  // do stuff...
}
 
int main() 
{
  std::thread foo;
  std::thread bar(mythread);

  std::cout << "Joinable after construction:\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';   // false 未执行时为不可等待的状态
  std::cout << "bar: " << bar.joinable() << '\n';   // true 执行了则可等待

  if (foo.joinable()) foo.join();
  if (bar.joinable()) bar.join();

  std::cout << "Joinable after joining:\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';   // 等待完都变成不可等待状态
  std::cout << "bar: " << bar.joinable() << '\n';

  return 0;
}