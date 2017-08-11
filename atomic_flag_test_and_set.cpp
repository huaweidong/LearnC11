// atomic_flag as a spinning lock　用作自旋锁
#include <iostream>       // std::cout
#include <atomic>         // std::atomic_flag
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

// test_and_set() 设置flag并返回设置之前的状态：状态有两种，已设置／未设置
// clear() 未设置状态

void append_number(int x) {
  while (lock_stream.test_and_set()) {} // 初始时flag=false,第一个线程跳出while循环，并且将flag=true，导致其他线程一直在while循环
  stream << "thread #" << x << '\n';
  lock_stream.clear();  // clear后flag=false,其他线程才可以执行
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=1; i<=10; ++i) threads.push_back(std::thread(append_number,i));
  for (auto& th : threads) th.join();

  std::cout << stream.str();
  return 0;
}