#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "EventLoop.h"

#include <string>
#include <functional>

namespace SNODE{

class Buff;
class Channel;

class TcpServer{
public:
	typedef std::function<void(Channel*, Buff&, int sz)>  MessageHandler;
	typedef std::function<void(int,int)>   ErrorHandFunc;

	TcpServer(unsigned int threadNum);

	void setMessageHandler(MessageHandler&& func) { messageHandler_ = std::move(func); }
	void setErrorHandFunc(ErrorHandFunc&& func){ errorHandFunc_ = std::move(func); }
	void setEventLoop(EventLoop* loop) { eventLoop_ = loop; }
	void startListen(std::string ip, int port);
	void onConnect(int fd);
private:
	MessageHandler messageHandler_;
	ErrorHandFunc  errorHandFunc_;

	EventLoop* eventLoop_;
	std::shared_ptr<EventLoopPool> eventLoopPool_;
};
}

#endif