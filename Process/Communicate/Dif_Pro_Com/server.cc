#include "common.hpp"

void CreatePipe(){
    int ret = mkfifo(FILENAME.c_str(), MODE);
    if(ret < 0){
        perror("mkfifo");
    } 
}

void Write(){
    while(true){
        cout << "Please Input@ ";
        int fd = open(FILENAME.c_str(), O_WRONLY);
        string mes;
        getline(cin, mes);
        write(fd, mes.c_str(), mes.size());
    }
}

void ClosePipe(){
    unlink(FILENAME.c_str());
}

int main(){
    CreatePipe();
    Write();
    ClosePipe();
    return 0;
}