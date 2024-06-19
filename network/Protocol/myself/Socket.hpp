//目的是设计一个相对通用的socket可以使客户端和服务器都可以使用
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <sys/socket.h>       
#include <netinet/in.h>
using namespace std;

const int BACKLOG = 10;
const uint16_t PORT = 8080;
const string IP = "0.0.0.0";
enum{
    SOCKFAIL = 1,
    BINDFAIL,
    LISTENFAIL,
    ACCEPTFAIL,
    CONNECTFAIL,
};

class Socket{
public: 
    Socket(uint16_t port = PORT, string ip = IP)
    :_port(port), _ip(IP){
        _sock = socket(AF_INET, SOCK_STREAM, 0);
        if(_sock < 0){
            perror("sock: ");
            exit(SOCKFAIL);
        }
    }
    //init 使初始化sockaddr_in
    void Init(sockaddr_in& so_addr){
        memcpy(&so_addr, 0, sizeof(so_addr));
        so_addr.sin_family = AF_INET;
        so_addr.sin_port = _port; 
        inet_aton(_ip.c_str(), &(so_addr.sin_addr));
    }

    bool Listen(){
        int n = listen(_sock, BACKLOG);
        if(n < 0){
            perror("listen fail: ");
            exit(LISTENFAIL);
        }
        return true;
    }

    bool Bind(){
        sockaddr_in local;
        Init(local);
        int n = bind(_sock, (sockaddr*)&local, sizeof(local));
        if(n < 0){
            perror("bind fail: ");
            exit(BINDFAIL);
        }
        return true;
    }

    bool Connect(){
        sockaddr_in peer;
        Init(peer);
        int n = connect(_sock, (sockaddr*)&peer, sizeof(peer));
        if(n < 0){
            perror("connect fail: ");
            exit(CONNECTFAIL);
        }
        return true;
    }

    int Accept(string& client_ip, uint16_t& client_port){
        //这两个是输出型参数，用来带走被连接者的ip和port
        sockaddr_in tmp;
        socklen_t len = sizeof(tmp);
        int sock_fd = accept(_sock, (sockaddr*)&tmp, &len);
        //进行提取操作
        client_port = tmp.sin_port;
        char ipstr[64];
        inet_ntop(AF_INET, &tmp.sin_addr, ipstr, sizeof(ipstr));
        client_ip = ipstr;
        return sock_fd;
    }

    int Fd(){
        return _sock;
    }

    void Close(){
        close(_sock);
    }

private:
    uint16_t _port;
    string _ip;
    int _sock;
};

















