#include "tcpserver.h"
#include "base/channel.h"
#include <functional>
#include <sys/epoll.h>

using namespace std::placeholders;

namespace SNODE{

TcpServer::TcpServer(std::shared_ptr<EventLoop> loop, std::string ip, int port):eventLoop_(loop){
	port_ = port;
	ip_     = ip;
}

void TcpServer::start(){
	Channel* ch = new Channel(0);
	ch->listenChannel(ip_, port_);
	//eventLoop_->doInLoop( std::bind(&EpollLooper::updateChannel, eventLoop_->looper_, EPOLL_CTL_ADD, ch) );
}
void TcpServer::stop(){
	
}

/*
EPOLL_CTL_ADD : 添加监听的事件
EPOLL_CTL_DEL : 删除监听的事件
EPOLL_CTL_MOD : 修改监听的事件
*/

void TcpServer::onConn(int fd){
	Channel* ch = new Channel(0);
	ch->setReadFunc( std::bind(&TcpServer::onRead, this, _1, _2, _3) );
	//eventLoop_->doInLoop( std::bind( &EpollLooper::updateChannel, eventLoop_->looper_, EPOLL_CTL_ADD, ch ) );
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

void TcpServer::onRead(const char* buff, int sz, Channel* ch){
	//std::cout<<buff<<std::endl;
}
}