#include<iostream>
#include<sys/types.h>
#include<signal.h>
using namespace std;

//kill signal pid
int main(int argc, const char* argv[]){
    if(argc != 3){
        cout << "Tip" << endl;
        cout << "kill signal pid" << endl << endl;
    }else{
        int signal = stoi(argv[1]);
        int pid = stoi(argv[2]);
        kill(pid, signal);
    }
    return 0;
}
