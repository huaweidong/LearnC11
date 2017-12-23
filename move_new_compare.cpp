#include <iostream>
#include <deque>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

typedef struct voiceData
{
    char *voice;
    int len;
    voiceData()
    {
        voice = NULL;
        len = 0;
    }
    voiceData(char *_v, int _l)
    {
        voice = _v;
        len = _l;
    }
    ~voiceData()
    {
        if (voice != NULL)
        {
            delete voice;
            voice = NULL;
        }
        len = 0;
    }
} CSGVoiceData;

deque<CSGVoiceData*> Q;
deque<vector<char>> Q2;
atomic<bool> bFlag(true);
mutex mux;
condition_variable cond;

void produce()
{
    char data[16000] = {0};
    for(int i = 0; i < 16000; i++)
    {        
        data[i] = rand()%100;
    }
    int i = 0;
    while(bFlag)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        i++;
        cout << "produce: " << i << endl;
        //char* voice = new char[16000];        
        //memcpy((void*)voice, (void*)data, 16000);
        vector<char> V(data, data+16000);
        unique_lock<mutex> lck(mux);
        //Q.push_back(new CSGVoiceData(voice, 16000));
        Q2.push_back(move(V));
        cond.notify_one();
    }
}

void consume()
{
    int i = 0;
    while(bFlag)
    {
        //CSGVoiceData* o = new CSGVoiceData();
        unique_lock<mutex> lck(mux);
        if(Q2.empty()) {
            cout << "consume: wait" << endl;
            cond.wait(lck);
        } else
        {
            i++;
            cout << "consume: " << i << endl;
            //CSGVoiceData *k = Q.front();
            /*if(k && k->voice && k->len != 0) {
                o->voice = new char[k->len];
                memcpy((void*)o->voice, (void*)k->voice, k->len);
                delete k;
                k = NULL;
            }
            Q.pop_front();
            */
            vector<char> V = move(Q2.front());
            Q2.pop_front();
        }
        //delete o;
        //o = 0;
    }
}

int main()
{
    srand(time(0));
    
    thread t1(produce);
    thread t2(consume);

    this_thread::sleep_for(chrono::seconds(5));
    bFlag = false;

    t1.join();
    t2.join();
    return 0;
}
