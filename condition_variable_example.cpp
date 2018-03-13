#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
using namespace std;

mutex g_mtx;
condition_variable g_cv;
bool ready = false;

void print_id(int i)
{
    unique_lock<mutex> lck(g_mtx);
    /*while(!ready) {
        g_cv.wait(lck);
    }*/
    g_cv.wait(lck, [](){return ready;});    // 只有当 pred 条件为 false 时调用 wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有当 pred 为 true 时才会被解除阻塞。
    // g_cv.wait_for(lck, Period, ...);// wait_for 可以指定一个时间段，在当前线程收到通知或者指定的时间 rel_time 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，wait_for 返回
    // wait_until 可以指定一个时间点，在当前线程收到通知或者指定的时间点 abs_time 超时之前，该线程都会处于阻塞状态。而一旦超时或者收到了其他线程的通知，wait_until 返回
    cout << "Thread " << i << endl;
}

void go()
{
    unique_lock<mutex> lck(g_mtx);
    ready = true;
    g_cv.notify_all();
}

int main()
{
    thread threads[10];
    for(int i = 0; i < 10; i++) {
        threads[i] = thread(print_id, i);
    }
    go();
    for(auto & th:threads) {
        th.join();
    }
    return 0;
}
