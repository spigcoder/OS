#include "Protocol.hpp"
#include "Socket.hpp"

const int SIZE = 1024;

enum{
    ARGVFAIL = 1,
};

void ServerStart(uint16_t port){
    Socket server(port);
    server.Bind();
    server.Listen();
    while(true){
        uint16_t client_port;
        string client_ip;
        int fd = server.Accept(client_ip, client_port);
        if(fd < 0){
            perror("connect fail:");
            continue;
        }
        cout << "connect to " << client_ip << " port: " << client_port;
        //进行服务
        if(fork() == 0){
            while(true){
                char buff[SIZE];
                //子进程进行服务
                ssize_t n = read(fd, buff, SIZE);
                if(n < 0){
                    perror("read fail");
                }
                buff[n] = 0;
                string messages = buff;
                //处理数据
                Request rq;
                rq.DeSerialize(messages);
                //rq现在已经是一些具体的数据了
                rq.Print();
                int ret = rq.Compute();
                Response rp(ret, 0);
                const string send_message = rp.Serialize();
                write(fd, send_message.c_str(), send_message.size());
                cout << "server have send a message to client" << endl;
            }
            exit(0);
        }
    }
}

int main(int argc, const char* argv[]){
    if(argc != 2){
        cout << "./server port" << endl;
        exit(ARGVFAIL);
    }
    uint16_t port = stoi(argv[1]);
    ServerStart(port);

    return 0;
}