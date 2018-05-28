#include "tcpserver.h"
#include "../base/channel.h"

namespace SNODE{

void TcpServer::TcpServer(std::string& ip, int port){
	std::shared_ptr<EpollLooper> epolllooper = std::shared_ptr<EpollLooper>(new EpollLooper(id, port));
	EventLoop*   eventloop   = new EventLoop(epolllooper, 0);
	eventLoop_ = std::shared_ptr<EventLoop>(eventloop);
}

void TcpServer::start(){
	eventLoop_.loop();
}
void TcpServer::stop(){

}

void TcpServer::onConn(int fd){
	Channel* ch = new Channel();
	ch->setReadFunc( std::bind(&TcpServer::onRead, this, _1, _2) );
	eventLoop_->doInLoop( std::bind( &EpollLooper::updateChannel, eventLoop_->looper_, EPOLL_ADD, ch ) );
}

void TcpServer::setMessageHandler(MessageHandler&& func){
	messageHandler_ = std::move(func);
}
void TcpServer::setConnectHandler(ConnectHandler&& func){
	connectHandler_ = std::move(func);
}

/*void TcpServer::setReadHandler(ReadHandler&& func){
	readhandler_ = std::move(func);
}*/

}