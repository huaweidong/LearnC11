// thread::get_id / this_thread::get_id
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds
 
std::thread::id main_thread_id = std::this_thread::get_id();    // 这里直接取主线程id

void is_main_thread() {
  if ( main_thread_id == std::this_thread::get_id() )
    std::cout << "This is the main thread.\n";
  else
    std::cout << "This is not the main thread.\n";
}

int main() 
{
  is_main_thread();
  std::thread th (is_main_thread);  // 如果线程是joinable的，则返回的是线程唯一标识符，如果不是，则返回一个默认构造的thread::id对象
  th.join();
}