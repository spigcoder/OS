#include<iostream>
#include<signal.h>
#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
using namespace std;

void Handler(int signal){
    cout << "I have get signal: " << signal << endl;
}

void TestSignal(){
    signal(SIGINT, Handler); 
    while(true){
        cout << "I'm a process my pid is " << getpid() << endl;
        sleep(1);
    }
}

//这里的行为和除0错误的行为一样
void TestSegv(){
    signal(SIGSEGV, Handler);
    int *p = nullptr;
    *p = 10;
    cout << *p << endl;
}

//当进行这样的配置的时候会一直进行打印，这是因为当出现SIGFPE错误时系统会向这个错误进程发信号，然后终止这个进程
//但是由于我手动的将这个信号的行为进行了更改，所以这个进程不会终止而这个进程的状态不改变，就会导致操作系统一直发信号
//而进程一直不终止，所以就会出现在屏幕上一直打印的现象
void TestFpe(){
    signal(SIGFPE, Handler);
    int a = 0;
    int b = 10;
    int c = b / a;
}

void TestExitAction(){
    //有些进程在被信号终止是会出现两种状态，一种是以core的方式退出还有一种是Term
    pid_t id = fork();
    if(id == 0){
        int cnt = 500;
        while(--cnt){
            cout << "I'm child my pid is " << getpid() << endl;
            sleep(1);
        }
    }else{
        int status = 0;
        waitpid(id, &status, 0);
        cout << "exit code: " << ((status>>8)&0xFF) << " exit signal: " << (status&0x7F) << " core dump: " << ((status>>7)&1) << endl; 
    }

}

int main(int argc, char* argv[]){
    //TestSignal();
    // TestFpe();
    // TestSegv();
    TestExitAction();
}