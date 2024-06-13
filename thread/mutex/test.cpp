#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;
const int NUM = 5;

//目的时做出一个多线程抢票系统，然后验证出来多线程的问题
//然后上一把锁，全局锁和局部锁都使用一下，最后封装一下锁使用一下RAII风格
//RAII风格就是把锁以及上锁和解锁的动作封装成为一个类，根据构造和析构来实现根据作用域来进行上锁和解锁操作
class TicketData{
public:
    TicketData(int num/*, pthread_mutex_t* lock*/){
        _name = "Thread-" + to_string(num);
        // _lock = lock;
    }
public:
    string _name;
    // pthread_mutex_t* _lock;
};

int ticket = 2000;

//实施抢票游戏
// void *TicketGame(void *args){
//     TicketData* tick = static_cast<TicketData*> (args);
//     string name = tick->_name;
//     while(true){
//         //上锁
//         pthread_mutex_lock(tick->_lock);
//         if(ticket > 0){
//             usleep(1);
//             cout << name << "get tickets: " << ticket << endl; 
//             ticket--;
//             //解锁
//             pthread_mutex_unlock(tick->_lock);
//         }else{
//             pthread_mutex_unlock(tick->_lock);
//             break;
//         }
//     }
//     return nullptr;
// }
//这样就不用进行初始化等操作了
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *TicketGame(void *args){
    TicketData* tick = static_cast<TicketData*> (args);
    string name = tick->_name;
    while(true){
        //上锁
        pthread_mutex_lock(&lock);
        if(ticket > 0){
            usleep(1);
            cout << name << "get tickets: " << ticket << endl; 
            ticket--;
            //解锁
            pthread_mutex_unlock(&lock);
        }else{
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return nullptr;
}

void TestMultiThread(){
    //局部锁
    // pthread_mutex_t lock;
    // pthread_mutex_init(&lock, nullptr);
    vector<pthread_t> tds;
    vector<TicketData*> ts;
    //创建多线程
    for(int i = 1; i <= NUM; ++i){
        pthread_t tid;
        TicketData* tick = new TicketData(i/*, &lock*/);
        pthread_create(&tid, nullptr, TicketGame, (void*)tick);
        ts.push_back(tick);
        tds.push_back(tid);
    }
    //释放资源并且等待线程结束
    for(auto e : tds){
        pthread_join(e, nullptr);
    }

    for(auto t : ts){
        delete t;
    }
    //这里的锁要等到线程都已经结束之后才能进行释放，早释放了相当于没有加锁
    // pthread_mutex_destroy(&lock);
}

int main(){
    TestMultiThread();
    return 0;
}