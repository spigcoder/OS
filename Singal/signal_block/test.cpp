#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;
sigset_t mset, oset;

void Handler(int sig){
    cout << "catch this signal: " << sig << endl;
}

sigset_t Block(){
    //2.1预处理信号
    sigemptyset(&mset);
    sigemptyset(&oset);
    sigaddset(&mset, 2);
    //2.2向系统中写入阻塞信号
    sigprocmask(SIG_SETMASK, &mset, &oset);
    return oset;
}

void PrintPendNum(){
    for(int i = 31; i >= 1; i--){
        if(sigismember(&mset, i))
            cout << 1;
        else 
            cout << 0;
    }
    cout << endl;
}

void TestBlock(){
    //1.自定义信号
    signal(2, Handler);    

    //2.阻塞2号信号
    Block();
    //实验
    int cnt = 10;
    while(cnt--){
        sigpending(&mset);
        PrintPendNum();
        sleep(1);
    }
    //解除阻塞状态
    sigprocmask(SIG_SETMASK, &oset, nullptr);
    sigpending(&mset);
    PrintPendNum();
}

//这里与信号行为自定义一样，对于9号和19号信号不能进行阻塞处理
int main(){
    TestBlock();
    return 0;
}



