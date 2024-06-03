#include"common.h"
#include<iostream>
#include<unistd.h>
using namespace std;

void test_client(){
    SMemory sm;
    int m_id = sm.GetMemory();
    char* mem = (char*)shmat(m_id, nullptr, 0);
    //默认server进行写入操作
    while(true){
        cout << "client get@ " << mem;
        sleep(1);
    }
    shmdt(mem);
}



int main(){
    test_client();
    return 0;
}
