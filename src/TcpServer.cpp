#include "TcpServer.h"
#include "Channel.h"

namespace SNODE{

	TcpServer::TcpServer(unsigned int threadNum){ 
		if(threadNum > 1 ){
			eventLoopPool_ = std::shared_ptr<EventLoopPool>(new EventLoopPool(threadNum));
		}
	}

	void TcpServer::startListen(std::string ip, int port){
		Channel* channel = new Channel(0);
		channel->setConnectHandFunc(std::bind(&TcpServer::onConnect, this,std::placeholders::_1));
		eventLoop_->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop_, 1, channel )  ); 
	}

	void TcpServer::onConnect(int fd){
		Channel* channel = new Channel(fd);
		channel->setMessageHandFunc(messageHandler_);
		//channel->setErrorHandler();
		if(eventLoopPool_ != NULL){
			auto eventLoop = eventLoopPool_->getEventLoop();
			eventLoop->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop, 1, channel ) );
		}else{
			eventLoop_->runInLoop( std::bind( &EventLoop::addToLooper, eventLoop_, 1, channel ) );
		}
	}
}