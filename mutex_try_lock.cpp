// mutex::try_lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

volatile int counter (0); // non-atomic counter
std::mutex mtx;           // locks access to counter

void attempt_10k_increases () {
  for (int i=0; i<10000; ++i) {
    //if (mtx.try_lock())    // only increase if currently not locked: 使用try_lock最后输出counter不是１０００００无法保证准确，用lock才可以
    // 1. 如果没有锁，则锁住并返回true
    // 2. 如果被另一个线程锁住，则返回false
    // 3. 如果已被当前线程锁住，则死锁
    // 4. 想要同一个线程锁多次，得用recursive_mutex,recursive_mutex和mutex比较最大的不同就是可以在同一个线程中重复加锁（每个锁一个级别），当然也必须调用同样多次解锁
    // 4. timed_mutex.try_lock_for会阻塞一定时间，到时间了则返回
    {
      mtx.lock();
      ++counter;
      mtx.unlock();
    }
  }
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(attempt_10k_increases);

  for (auto& th : threads) th.join();
  std::cout << counter << " successful increases of the counter.\n";

  return 0;
}