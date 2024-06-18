#include <string>       
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;

const int SIZE = 1024;
const int back_log = 5;
const uint16_t PORT = 8888;
const string IP = "0.0.0.0";

enum{
    SOCKFAIL = 1,
    BINDFAIL,
    LISTENFAIL
};

class TcpSocket;

struct SockData{
public:
    SockData(sockaddr_in local, TcpSocket* this_, int socket)
    :_local(local), _this(this_), _socket(socket) 
    {}

public:
    sockaddr_in _local;
    TcpSocket* _this;
    int _socket;
};

class TcpSocket{
public:
    TcpSocket(uint16_t port = PORT, string ip = IP):_ip(IP), _port(PORT)
    {
        _listen_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(_listen_socket < 0){
            perror("socket fail: ");
            exit(SOCKFAIL);
        }
    }

    void Init(sockaddr_in& local){
        _local.sin_family = AF_INET;
        _local.sin_port = htons(_port);
        inet_aton(_ip.c_str(), &(_local.sin_addr));
    }

    void Server(){
            Init(_local);
            socklen_t len = sizeof(_local);
            //进行绑定
            int n = bind(_listen_socket, (sockaddr*)&_local, len);
            if(n < 0){
                perror("bind fail ");
                exit(BINDFAIL);
            }
            //进行监听
            int x = listen(_listen_socket, back_log);
            if(x < 0){
                perror("listen fail ");
                exit(LISTENFAIL);
            }
            //执行代码
            Run();
    }
    static void* Routine(void *args){
        pthread_detach(pthread_self());
        string message;
        SockData* data = static_cast<SockData*>(args);
        while(true){
            char buff[SIZE];
            //进行数据的处理
            ssize_t n = read(data->_socket, buff, sizeof(buff));
            buff[n] = 0;
            //将消息发送给客户端
            string log = buff;
            message = inet_ntoa((data->_local).sin_addr);
            message = "[" + message + "]$ " + log;
            ssize_t x = write(data->_socket, message.c_str(), message.size());
            cout << "get data message" << message << endl;
        }
        delete data;
    }

    void Run(){
        //接收连接到的信号
        sockaddr_in client;
        socklen_t len = sizeof(client);
        while(true){
            int socket = accept(_listen_socket,(sockaddr*)&client, &len);
            //这个socket是用来通信的，tcp是面向字节流进行通信的，所以使用起来就和文件一样
            //这里就可以分出线程去执行通信的代码，然后主线程继续接收操作
            pthread_t id;
            SockData* data = new SockData(client, this, socket);
            pthread_create(&id, nullptr, Routine, data);
        }

    }

    ~TcpSocket(){
        close(_listen_socket);
    }
private:
    int _listen_socket;
    uint16_t _port;
    string _ip;
    sockaddr_in _local;
};