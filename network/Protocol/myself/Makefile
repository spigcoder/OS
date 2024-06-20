.PHONY:all
all: server client

lib=Protocol.hpp Socket.hpp

server:Server.cc $(lib) -lpthread
	g++ -o $@ $< -std=c++11

client:Client.cc $(lib) -lpthread
	g++ -o $@ $< -std=c++11

.PHONY:clean
clean: 
	rm -f server client