#include <iostream>
#include "../src/tcpserver.h"

int main(int argc, char** argv){
	TcpServer server;
	server.listen(std::string("127.0.0.1"), 8001);
	server.start();
}