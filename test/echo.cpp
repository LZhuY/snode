#include "echo.h"
#include "./src/base/Channel.h"

void Echo::setEventLoop(std::shared_ptr<EventLoop>& loop){
	eventLoop_ = loop;
}
void Echo::setMessageHandler(MessageHandler&& func){
	messageHandler_ = std::move(func);
}

void Echo::setTcpServer(TcpServer* server){
	server_ = server;
	server_->setMessageHandler( std::bind( &Echo::onMessageHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ));
}

void Echo::onMessageHandler(Channel* ch, const char* msg, int sz){
	if(messageHandler_)
		messageHandler_(ch, msg, sz);
}