#include "TcpServer.h"
#include "Channel.h"
extern "C"{
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <sys/epoll.h>
	#include <arpa/inet.h>
	#include <string.h>
}

namespace SNODE{

	TcpServer::TcpServer(unsigned int threadNum){ 
		if(threadNum > 1 ){
			eventLoopPool_ = std::shared_ptr<EventLoopPool>(new EventLoopPool(threadNum));
		}
		else
		{
			//eventLoopPool_ = NULL;
		}
	}

	void TcpServer::startListen(std::string ip, int port){
		int code = 0;
		struct sockaddr_in addr;
		int fd = socket(AF_INET, SOCK_STREAM, 0);
		
		if(fd == -1){
			std::cout<< "socket error" << std::endl;
			return;
		}
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port);

		code = bind( fd, (struct sockaddr*)&addr, sizeof(addr) ) ;
		if(code == -1){
			std::cout << "bind error" << std::endl;
			return;
		}

		socket_non_blocking(fd);
		code = listen(fd, 10);
		if(code == -1){
			std::cout<< "listen error" << std::endl;
			return;
		}
		std::cout<< "listen" << std::endl;

		Channel* channel = new Channel(fd, true);
		channel->events_ = EPOLL_CTL_ADD;

		channel->setConnectHandFunc(std::bind(&TcpServer::onConnect, this,std::placeholders::_1));
		eventLoop_->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop_, 1, channel )  ); 
	}

	void TcpServer::onConnect(int fd){
		std::cout << "TcpServer::onConnect" << std::endl;
		Channel* channel = new Channel(fd, false);
		channel->setMessageHandFunc(messageHandler_);
		channel->events_ = EPOLL_CTL_ADD;
		//channel->setErrorHandler();
		//if(eventLoopPool_ != NULL){
			//auto eventLoop = eventLoopPool_->getEventLoop();
			//eventLoop->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop, 1, channel ) );
		//}else{
			eventLoop_->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop_, 1, channel ) );
		//}
	}

	Channel* TcpServer::connect2Node(int sid, std::string ip, int port){
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip.c_str());

		int fd = socket(AF_INET, SOCK_STREAM, 0);
		connect(fd, (struct sockaddr*)&addr, sizeof(addr));
		Channel* channel = new Channel(fd, false);
		channel->events_ = EPOLL_CTL_ADD;
		eventLoop_->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop_, 1, channel ) );
		channels_[sid] = channel;

		Buff buff;
		int fid = 101;
		buff >> fid;
		buff.addSize();
		channel->writeToChannel(buff.data(), buff.size());

		return channel;
	}
}