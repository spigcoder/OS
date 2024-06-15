#include"RunQueue.hpp"
#include <unistd.h>
using namespace std;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *Consumer(void *args){
    RunQueue<int>* bf = static_cast<RunQueue<int>*>(args);
    int sz = 10;
    while(true){
        sleep(1);
        int x = bf->pop();
        pthread_mutex_lock(&lock);
        cout << "Consumer get a num: " << x << endl; 
        pthread_mutex_unlock(&lock);
    }
    return nullptr;
}

void *Producer(void *args){
    RunQueue<int>* bf = static_cast<RunQueue<int>*>(args);
    int num = 1;
    int sz = 10;
    while(true){
        bf->push(num);
        pthread_mutex_lock(&lock);
        cout << "Producer have produce a product" << endl;
        pthread_mutex_unlock(&lock);
        num++;
        cout << num << endl;
    }
    return nullptr;
}

void TestPC(){
    pthread_t c, p;
    RunQueue<int>* bf = new RunQueue<int>;
    //创建两个线程
    pthread_create(&c, nullptr, Consumer, bf);
    pthread_create(&p, nullptr, Producer, bf);
    //进行线程等待
    pthread_join(p, nullptr);
    pthread_join(c, nullptr);
    delete bf;
}

int main(){
    TestPC();
    return 0;
}