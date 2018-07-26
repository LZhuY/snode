#include "echo.h"
#include "../src/base/Channel.h"

using namespace SNODE;

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

void Echo::onMessageHandler(Channel* ch, Buff& buff, int sz){
	if(messageHandler_)
		messageHandler_(ch, buff, sz);
}