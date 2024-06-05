#include<iostream>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

void handler(int signal){
    cout << "I have get signal: " << signal << endl;
}

int main(int argc, char* argv[]){
    signal(SIGINT, handler); 
    while(true){
        cout << "I'm a process my pid is " << getpid() << endl;
        sleep(1);
    }
}