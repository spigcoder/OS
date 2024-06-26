#include "HttpServer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        exit(1);
    }
    
    uint16_t port = std::stoi(argv[1]);
    // HttpServer *svr = new HttpServer();
    // std::unique<HttpServer> svr(new HttpServer());
    Server* ser = new Server(port);
    ser->Start();
    delete ser;
    return 0;
}