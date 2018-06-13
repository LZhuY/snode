#include "src\base\Looper.h"
#include "src\base\Channel.h"
#include "src\base\EpollLooper.h"
#include "src\base\EventLoop.h"
#include "src\base\TcpServer.h"
#include "echo.h"

#include <iostream>
#include <memory>
#include <string>

using namespace SNODE;

void MessageHandler(Channel* ch, const char* msg, int sz){
	std::cout<< msg << " " << sz << std::endl;
	ch->writeToChannel(msg, sz);
}

int main(int argc, char** argv){	
	EpollLooper epollLooper;
	EventLoop eventLoop(-1);
	eventLoop.setLooper( &epollLooper );
	
	TcpServer server(8);
	server.setEventLoop( &eventLoop );
	server.startListen(std::string("127.0.0.1"), 8900);
	
	Echo echo;
	echo.setTcpServer(&server);
	echo.setMessageHandler( std::bind(MessageHandler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );

	eventLoop.loop();
	std::cout<< "main fun end" << std::endl;
	return 0;
}