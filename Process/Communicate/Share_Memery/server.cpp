#include"common.h"
#include<iostream>
using namespace std;

void test_server(){
    SMemory sm;
    int m_id = sm.CreateMemory();
    char* mem = (char*)shmat(m_id, nullptr, 0);
    //默认server进行写入操作
    while(true){
        cout << "server say@ ";
        fgets(mem, sm.size(), stdin);
    }
    shmdt(mem);
}



int main(){
    test_server();
    return 0;
}