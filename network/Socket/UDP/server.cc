#include "UdpSocket.hpp"
#include <memory>

const int ARGCFAIL = 1;

string func(const string& str){
    string tmp = "client say $: " + str;
    return tmp;
}

void ServerTest(int port){
    unique_ptr<UdpSocket> server(new UdpSocket(port)); 
    server->Server(func);
}

int main(int argc, const char* args[]){
    if(argc != 2){
        cout << "you should type port to server" << endl;
        exit(ARGCFAIL);
    }
    uint16_t port = stoi(args[1]); 
    ServerTest(port);
}