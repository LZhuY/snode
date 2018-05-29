#include <iostream>
#include "../src/tcpserver.h"

using namespace SNODE;

int main(int argc, char** argv){
	EpollLooper epollLooper;
	EventLoop eventLoop(epollLooper, 0);
	TcpServer server(eventLoop, std::string("ip"), 8900);
	server.start();
	eventLoop.loop();
}