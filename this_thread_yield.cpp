// this_thread::yield example
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::yield
#include <atomic>         // std::atomic

std::atomic<bool> ready (false);

void count1m(int id) {
  while (!ready) {             // wait until main() sets ready...
    std::this_thread::yield();  // 由运行状态变成可调度状态，释放CPU，但是扔可以快速进入运行状态，和sleep的区别是sleep会真的等到一定时间，这个用于需要即时响应的情况
    std::cout << "wait" << std::endl;   // 会打印超多次
  }
  for (volatile int i=0; i<1000000; ++i) {}
  std::cout << "thread " << id << "finished." << std::endl;;
}

int main ()
{
  std::thread threads[10];
  std::cout << "race of 10 threads that count to 1 million:\n";
  for (int i=0; i<10; ++i) threads[i]=std::thread(count1m,i);
  std::this_thread::sleep_for (std::chrono::seconds(1));
  ready = true;               // go!
  for (auto& th : threads) th.join();
  std::cout << '\n';

  return 0;
}