#pragma once
#include <iostream>
#include <pthread.h>
#include <queue>
using namespace std;

/*实现目标：实现一个类，里面生产者和消费者通过push和pop操作来堆BufferQueue来进行操作
要保证push和pop的同步和互斥性*/

template <class T>
class BufferQueue{
private:
    static const int default_size = 10;
public:
    BufferQueue(const int max_size = default_size)
    :_max_size(max_size), _low_water(default_size / 3)
    , _high_water(default_size*2/3){
        //进行各个锁和条件变量的初始化
        pthread_mutex_init(&_lock, nullptr);
        pthread_cond_init(&_c_con, nullptr);
        pthread_cond_init(&_c_con, nullptr);
    }

    //这里进行push 和 pop操作
    void push(T data){
        //_q是临界资源，对于临界资源的访问要上锁
        pthread_mutex_lock(&_lock);
        //这里要用while循环来进行判断，这样才可以保证不会出现伪唤醒的情况
        while(_q.size() == _max_size){
            //当容器的容量等于可以承受的最大容量时，要进行等待
            pthread_cond_wait(&_p_con, &_lock);
        }
        _q.push(data);
        //如果现在容器中的内容高于high_water可以唤醒消费者
        if(_q.size() > _high_water) pthread_cond_signal(&_c_con);
        pthread_mutex_unlock(&_lock);
    }

    T pop(){
        pthread_mutex_lock(&_lock);
        while(_q.size() == 0){
            //当容器的容量等于可以承受的最大容量时，要进行等待
            pthread_cond_wait(&_c_con, &_lock);
        }
        T val = _q.front(); 
        _q.pop();
        if(_q.size() < _low_water) pthread_cond_signal(&_p_con);
        pthread_mutex_unlock(&_lock);
        return val;
    }

    ~BufferQueue(){
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_c_con);
        pthread_cond_destroy(&_p_con);
    }
    
private:    
    queue<T> _q;
    const int _max_size;
    pthread_mutex_t _lock;
    //两个同步等待队列，分别等待coustomer和prodecer
    pthread_cond_t _c_con;
    pthread_cond_t _p_con;
    //这两个水位分别表示唤醒等待队列的大致时间
    const size_t _low_water;
    const size_t _high_water;
};