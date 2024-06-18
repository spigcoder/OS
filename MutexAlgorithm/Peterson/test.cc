#include <iostream>
#include <pthread.h>
using namespace std;
//flag是实现这个算法的关键
int flag[2] = {0, 0};
int turn = 0;
int sum = 0;

void* P0(void *args){
    int size = 100000;
    while(true){
        //表明P0要进入临界区
        flag[0] = true;
        //设置对方的turn
        turn = 1;
        //如果对方也想进入并且当前是对方的回合就等待，否则直接进入临界区
        while(flag[1] && turn == 1);

        //进入临界区
        while(size--){
            sum += 1;
        }
        cout << "P0 get sum: " << sum << endl;
        //释放资源
        flag[0] = false;
        break;
    }
    return nullptr;
}

void* P1(void* args){
    int size = 100000;
    while(true){
        //表明P1要进入临界区
        flag[1] = true;
        turn = 0;
        while(flag[0] && turn == 0);

        //进入临界区
        while(size--){
            sum += 1;
        }
        cout << "P1 get sum: " << sum << endl;
        //释放资源
        flag[1] = false;
        break;
    }
    return nullptr;
}

void* test1(void *args){
    int size = 100000;
    while(size--){
        sum += 1;
    }
    return nullptr;
}

void* test2(void *args){
    int size = 100000;
    while(size--){
        sum += 1;
    }
    return nullptr;
}

int main(){
    pthread_t p0, p1;
    pthread_create(&p0, nullptr, P0, nullptr);
    pthread_create(&p1, nullptr, P1, nullptr);
    // pthread_create(&p0, nullptr, test1, nullptr);
    // pthread_create(&p1, nullptr, test2, nullptr);
    pthread_join(p0, nullptr);
    pthread_join(p1, nullptr);
    cout << sum << endl;
    return 0;
}