#include <time.h>
#include <cstdlib>
#include "Socket.hpp"
#include "Protocol.hpp"

const int OPSIZE = 3;
const int SIZE = 1024;
enum{
    ARGVFAIL = 1,
};

const char _op[] = {'+', '-', '*'};

void ClientStart(uint16_t port, const string& ip){
    Socket client(port, ip);
    client.Connect();
    while(true){
        //开始发送消息
        int x = rand() % 100; 
        int y = rand() % 100; 
        char op = _op[rand() % OPSIZE];
        Request rq(x, op, y);
        string send_message = rq.Serialize();
        write(client.Fd(), send_message.c_str(), send_message.size());
        cout << "client send a message to server" << endl;
        sleep(1);
        char buff[SIZE];
        ssize_t n = read(client.Fd(), buff, SIZE);
        if(n < 0){
            perror("read fail: ");
        }
        buff[n] = 0;
        Response rp;
        string message = buff;
        rp.DeSerialize(message);
        rp.Print();
    }
}


int main(int argc, const char* argv[]){
    if(argc != 3){
        cout << "you should type ./client ip port" << endl;
        exit(ARGVFAIL);
    }
    srand(time(nullptr)^getpid());
    uint16_t port = stoi(argv[2]);
    string ip = argv[1];
    ClientStart(port, ip);
    return 0;
}