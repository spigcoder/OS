#include "TcpSocket.hpp"
#include <cstring>

int main(int argc, const char* argv[]){
    uint16_t port = stoi(argv[1]);
    TcpSocket server(port);
    server.Server();
    return 0;
}