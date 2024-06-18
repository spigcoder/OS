#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <functional>
using namespace std;

//实现一个基本的UdpSocket功能
const string IP = "0.0.0.0";
const uint16_t PORT = 8080;
const int SIZE = 1024;
using func_t = function<string(const string &)>;
using sockaddr_in = struct sockaddr_in;
using sockaddr = struct sockaddr;


enum{
    SOCKETFAIL = 1,
    BINDFAIL
};


class UdpSocket{
    //用户可以自己传递id和port
public:
    UdpSocket(const uint16_t& port = PORT, const string& ip = IP)
    :_ip(ip), _port(port), _is_running(false){
        //创建socketfd
        //三个参数分别表示ip4, 数据包传输等
        cout << _ip << " " << _port << endl;
        _socketfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(_socketfd < 0){
            perror("socket fail");
            exit(SOCKETFAIL);
        }
        cout << "socket sucess socketfd is: " << _socketfd << endl;
    }

    void Server(func_t func){
        sockaddr_in local;
        Init(&local, sizeof(local));
        //进行连接
        int ret = bind(_socketfd, (const sockaddr*)&local, (socklen_t)sizeof(local));
        if(ret < 0){
            perror("bind fail ");
            exit(BINDFAIL);
        }
        cout << "bind sucess " << endl;
        Run(func);
    }

    //局部变量做返回值出了作用域就销毁了 
     void Init(sockaddr_in* local, size_t len){
        //socket已经创建过了，接下来进行连接操作
        bzero(local, len);
        //这里边分别由sin_family, sin_port, sin_addr
        (local->sin_addr).s_addr = inet_addr(_ip.c_str()); /*这里有两个动作，1. 将字符串转化为数字 2. 将其转化为大端（网络序） */
        local->sin_port = htons(_port); /*转化为网络序*/
        local->sin_family = AF_INET; /*告诉系统这个套接字是ipv4*/
    }

    //进行操作
    void Run(func_t func){
        _is_running = true;
        char buff[SIZE];
        while(_is_running){
            //从客户端得到数据
            sockaddr_in client;
            socklen_t len = sizeof(client);
            ssize_t n = recvfrom(_socketfd, buff, sizeof(buff) - 1, 0, (sockaddr*)&client, &len);
            buff[n] = 0;
            cout << "nihao " << endl;
            string log = buff;
            string out = func(log);
            sendto(_socketfd, out.c_str(), out.size(), 0, (const sockaddr*)&client, len);
            cout << out << endl;
        }
    }
    
    void Client(){
        sockaddr_in server;
        Init(&server, sizeof(server));
        string message;
        socklen_t slen = sizeof(server);
        char buff[SIZE];
        while(true){
            //得到数据
            cout << "clint type data: ";
            std::getline(cin, message);
            //cout << message << endl;
            //向终端服务器发送数据
            sendto(_socketfd, message.c_str(), message.size(), 0, (sockaddr*)&server, slen);
            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            ssize_t s = recvfrom(_socketfd, buff, SIZE - 1, 0, (sockaddr*)&temp, &len);
            if(s > 0){
                buff[s] = 0;
                cout << buff << endl;
            }
        }
    }
    
    ~UdpSocket(){
        if (_socketfd > 0) close(_socketfd);
    }

private:
    int _socketfd;
    string _ip;
    uint16_t _port;
    bool _is_running; 
};