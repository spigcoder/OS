#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
using namespace std;

const int NUM = 4;

//thread()
void *ThreadRoutine(void *args){
    int num = 10000;
    while(num--){
        i++;
    }
    return nullptr;
}

void TestThread(){
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadRoutine, nullptr);
    int num = 100000;
    while(num--){
        i++;
    }
    pthread_join(tid, nullptr);
}

//测试多线程并证明每个线程有自己独立的栈结构
void *TestMultiThread(void *args){
    int i = 0;
    int num = 10;
    while(num--){
        //这里可以证明每个线程都有自己独立的栈结构，但是像这样的打印也是不安全的
        //因为他会访问共享资源：显示器，这就会出现乱打印的现象
        cout << "i: " << i << " &i: " << &i << endl;
        i++;
        sleep(1);
    }
    return nullptr;
}

void TestMThread(){
    vector<pthread_t> tids;
    for(int i = 0; i < NUM; ++i){
        pthread_t id;
        pthread_create(&id, nullptr, TestMultiThread, nullptr);
        tids.push_back(id);
    }

    for(int i = 0; i < NUM; ++i){
        pthread_join(tids[i], nullptr);
    }
}

int main(){
    // TestThread();
    // TestMThread();
    return 0;
}