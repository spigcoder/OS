#include<iostream>
#include<vector>
#include<sys/types.h>
#include<unistd.h>
#include<string>
#include<cstdlib>
#include<sys/wait.h>
using namespace std;
typedef void (*func)();

class Channel{
public:
    Channel(pid_t id, int pipefd, string str)
        :_id(id), _pipefd(pipefd), _name(str) 
        {}
public:
    pid_t _id;
    int _pipefd;
    string _name;
};

void task1(){
    cout << "LoL 更新野怪" << endl;
}

void task2(){
    cout << "LoL 更新英雄血量" << endl;
}

void LoadTasks(vector<func>* tasks){
    tasks->push_back(task1);
    tasks->push_back(task2);
}