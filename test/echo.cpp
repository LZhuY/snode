#include <iostream>
#include "../src/tcpserver.h"
#include "../src/base/epolllooper.h"

using namespace SNODE;

int main(int argc, char** argv){
	EpollLooper epollLooper;
	std::shared_ptr<EpollLooper> looPtr(&epollLooper);
	EventLoop eventLoop(looPtr, 0);

	std::shared_ptr<EventLoop> elPtr(&eventLoop);
	TcpServer server(elPtr, std::string("ip"), 8900);
	server.start();
	eventLoop.loop();
}