.PHONY:all
all: server client

server:server.cc TcpSocket.hpp -lpthread
	g++ -o $@ $< -std=c++11

client:client.cc TcpSocket.hpp -lpthread
	g++ -o $@ $< -std=c++11

.PHONY:clean
clean: 
	rm -f server client