#include "../src/base/Looper.h"
#include "../src/base/Channel.h"
#include "../src/base/EpollLooper.h"
#include "../src/base/EventLoop.h"
#include "../src/base/TcpServer.h"
#include "../src/base/Buff.h"
#include "echo.h"

#include <signal.h> 
#include <unistd.h> 

#include <iostream>
#include <memory>
#include <string>

using namespace SNODE;

void sigroutine(int sig) {
switch (sig) { 
	case 1: 
		printf("Get a signal -- SIGHUP");
		break; 
	case 2: 
		printf("Get a signal -- SIGINT"); 
		break; 
	case 3: 
		printf("Get a signal -- SIGQUIT "); 
		break;
	default:
		printf("Get a signal -- SIGQUIT "); 
	} 
	return;
} 

void MessageHandler(Channel* ch, SNODE::Buff& buff, int sz){
	std::cout<< buff.data() << " " << sz << std::endl;
	ch->writeToChannel(buff.data(), sz);
}

int main(int argc, char** argv){

	signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法 
	signal(SIGINT, sigroutine); 
	signal(SIGQUIT, sigroutine);

	EpollLooper epollLooper;
	EventLoop eventLoop(-1);
	eventLoop.setLooper( &epollLooper );
	
	TcpServer server(0);
	server.setEventLoop( &eventLoop );
	server.startListen(std::string("127.0.0.1"), 9981);
	
	Echo echo;
	echo.setTcpServer(&server);
	echo.setMessageHandler( std::bind(MessageHandler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );

	eventLoop.loop();
	std::cout<< "main fun end" << std::endl;
	return 0;
}