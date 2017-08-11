// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
void foo() 
{
  // do stuff...
  printf("foo\n");
}

void bar(int x, int y)
{
  // do stuff...
  printf("bar x=%d y=%d\n", x, y);
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo() 初始化就相当于直接新建线程了
  std::thread second (bar,0,2);  // spawn new thread that calls bar(0) 参数是可变长的

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}