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
         //如果flag[0] = false表明P1还未进入临界区，他也进不来，那么P0就可以进入
        while(flag[1]){    
            //走到这里就表明P1也进入了这个缓冲区
            //如果turn == 0那么证明这次该我进入缓冲区，只要继续检查flag[1]的值，等待他将资源进行释放
            if(turn == 1){
                //turn == 1表明这次本来应该由1好进程进入，那么我就进行等待
                flag[0] = false;
                //这里是进行等待
                while(turn == 1);
                flag[0] = true;
            }
        }
        //这里就表示进入了缓冲区
        while(size--){
            sum += 1;
        }
        cout << "P0 get sum: " << sum << endl;
        //释放资源
        turn = 1;
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
        while(flag[0]){     //如果flag[1] = false表明P0还未进入临界区，他也进不来，那么P1就可以进入
            //走到这里就表明P0也进入了这个缓冲区
            //如果turn == 1那么证明这次该我进入缓冲区，只要继续检查flag[0]的值，等待他将资源进行释放
            if(turn == 0){
                //turn == 0表明这次本来应该由0号进程进入，那么我就进行等待
                flag[1] = false;
                //这里是进行等待
                while(turn == 0);
                flag[1] = true;
            }
        }
        //这里就表示进入了缓冲区
        while(size--){
            sum += 1;
        }
        cout << "P1 get sum: " << sum << endl;
        //释放资源
        turn = 0;
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