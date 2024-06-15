#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <semaphore.h>

const size_t DEFAULT = 10;

template<class T>
class RunQueue{
public:
    //semaphore表示的是默认信号量的个数，因为信号量本质上是一个计数器
    RunQueue(const size_t semaphore = DEFAULT)
    :_run_queue(semaphore)
    {
        //最后一个参数表示的是信号量初始化为多少
        sem_init(&_c_data, 0, 0); 
        sem_init(&_p_space, 0, semaphore); 
        pthread_mutex_init(&_p_mutex, nullptr);
        pthread_mutex_init(&_c_mutex, nullptr);
    }

    //分别进行push和pop操作
    void push(const T& data){
        //这里有一个思考的点，是先申请信号量还是先上锁 -> 先申请信号量
        //1. 申请信号量是原子操作，不需要锁来进行保护
        //2. 如果是先上锁，那么申请信号量就变成了单线程操作，这样就没有了多线程的优势

        //申请信号量, push 申请的是空间的信号量
        sem_wait(&_p_space);
        pthread_mutex_lock(&_p_mutex);
        _run_queue[_p_subscript++] = data;
        _p_subscript %= DEFAULT;
        pthread_mutex_unlock(&_p_mutex);
        //这里， 增加的是数据的信号量，这样才可以被拿到
        sem_post(&_c_data);
    }

    T pop(){
        //申请信号量, pop 申请的是数据的信号量
        sem_wait(&_c_data);
        pthread_mutex_lock(&_p_mutex);
        T data = _run_queue[_c_subscript++];
        _c_subscript %= DEFAULT;
        pthread_mutex_unlock(&_p_mutex);
        //这里， 增加的是位置的信号量，这样才可以继续进行写入
        sem_post(&_p_space);
        return data;
    }

    ~RunQueue(){
        sem_destroy(&_c_data);
        sem_destroy(&_p_space);
        pthread_mutex_destroy(&_p_mutex);
        pthread_mutex_destroy(&_c_mutex);
    }

private:
    //这是一个环形队列，
    std::vector<T> _run_queue;
    //用两个变量分别来表示生产者和消费者的下标
    size_t _c_subscript = 0;
    size_t _p_subscript = 0;

    //两个信号量用于标记剩余的空间和已经存在的任务
    sem_t _c_data;
    sem_t _p_space;

    //两把互斥锁分别作用于多生产者和多消费者的情况
    pthread_mutex_t _p_mutex;
    pthread_mutex_t _c_mutex;
};