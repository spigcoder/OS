.PHONY:all
all: server client

server:server.cc UdpSocket.hpp
	g++ -o $@ $< -std=c++11

client:client.cc UdpSocket.hpp
	g++ -o $@ $< -std=c++11

.PHONY:clean
clean: 
	rm -f server client