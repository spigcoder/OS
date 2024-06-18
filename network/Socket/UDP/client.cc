#include <memory>
#include "UdpSocket.hpp"

enum{
    ARGSFAIL = 1
};


int main(int argc, const char* args[]){
    if(argc != 3){
        cout << "you should type ./client ip port" << endl;
        exit(ARGSFAIL);
    }
    string ip = args[1];
    uint16_t port = stoi(args[2]);
    unique_ptr<UdpSocket> client(new UdpSocket(port, ip));
    cout << port << " " << ip << endl;
    client->Client();
}
