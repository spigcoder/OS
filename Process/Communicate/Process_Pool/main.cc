#include"Pool.hpp"
const size_t PROCESSNUM = 10;
const int TASKNUM = 2;
//规定父进程写入，子进程读出
vector<func> task;

void slaver(){
    //从管道中读取对应的数据并执行,因为已经重定向过了，所以直接从标准输入中读取即可
    while(true){
        cout << "I'm a child my pid is " << getpid() << " " << endl;
        int test_code;
        ssize_t n = read(0, &test_code, sizeof(test_code));
        if(n == -1 || n != sizeof(test_code)) break;
        //从test_code的值来决定执行什么函数
        task[test_code]();
        sleep(1);
    }
}

//创建管道，并将各个管道分配给各个子进程，同时关闭不需要的管道
void Init(vector<Channel>* Channels){
    int pipefd[2];
    vector<int> old_fd;
    for(size_t i = 0; i < PROCESSNUM; ++i){
        pipe(pipefd);
        pid_t id = fork();
        if(id == 0){
            //关闭子进程对于其兄弟进程的写端
            for(auto fd : old_fd) close(fd);
            close(pipefd[1]);
            //这样重定向之后就可以从标准输入中读取了
            dup2(pipefd[0], 0);
            slaver();
            exit(0);
       }else{
        string process_name = "Pid-" + to_string(i);     
        Channels->push_back(Channel(id, pipefd[1], process_name));
        old_fd.push_back(pipefd[1]);
       }
    }
}

void ProcessControl(const vector<Channel>& Channels){
    int num = 3;
    while(num--){
        //选择任务 
        int test_code = rand() % TASKNUM;
        //选择子进程
        int children = rand() % PROCESSNUM;
        //相对应的进程中写入任务让其执行
        write(Channels[children]._pipefd, &test_code, sizeof(test_code));
        sleep(1);
    }
}

void ProcessQuit(const vector<Channel> Channels){
    for(auto channel : Channels){
        close(channel._pipefd);
        waitpid(channel._id, nullptr, 0); 
    }
}

int main(){
    LoadTasks(&task);
    srand(time(nullptr));
    vector<Channel> Channels;
    Init(&Channels);
    //通过Channels来对各个子进程进行控制
    ProcessControl(Channels);
}