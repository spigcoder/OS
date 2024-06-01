#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<cstdlib>
#include<fcntl.h>
#include<cstdio>
#include<cerrno>
#include<string>
using namespace std;

const int sz = 1024;

void Write(int wfd){
    string mes = "I'm child my pid is ";
    int num = 0;
    pid_t id = getpid();
    char message[sz];
    while(true){
        //清空信息
        message[0] = 0;
        sprintf(message, "%s%d-num: %d",mes.c_str(), id, num);
        // write(wfd, message, strlen(message));
        //验证管道的大小
        char c = 'c';
        write(wfd, &c, 1);
        num++;
        // sleep(1);
        cout << num << endl;
    }
}

void Read(int rfd){
    char buf[sz];
    while(true){
        sleep(20);
        ssize_t n = read(rfd, buf, sizeof(buf));
        if(n) buf[n] = 0; 
        printf("I' father my pid is %d, message is %s, n : %ld\n",getpid(), buf, n);
    }
}

void IPC(){
    int pipefd[2];
    //[0]表示读，[1]表示写
    pipe(pipefd);
    pid_t id = fork();
    if(id == 0){
        //child -> w
        close(pipefd[0]);
        Write(pipefd[1]);
        exit(0);
    }else{
        close(pipefd[1]);
        Read(pipefd[0]);
        wait(nullptr);
    }

}

int main(){
    IPC();
    return 0;
}