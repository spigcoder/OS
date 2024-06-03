.PHONY:all
all: server client

server:server.cpp
	g++ -std=c++11 -o $@ $< -g

client:client.cpp
	g++ -std=c++11 -o $@ $< -g

.PHONY:clean
clean:
	rm -f client server pipe.txt
