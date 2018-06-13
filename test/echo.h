#ifndef _ECHO_H_
#define _ECHO_H_

#include "../src/base/TcpServer.h"
#include "../src/base/EventLoop.h"

using namespace SNODE;

class Echo {
public:
	typedef std::function<void(Channel*, const char* , int sz)> MessageHandler;

	Echo(){}
	~Echo(){}

	void setEventLoop(std::shared_ptr<EventLoop>& loop);
	void setTcpServer(TcpServer* server);
	void setMessageHandler(MessageHandler&& func);
	void onMessageHandler(Channel*, const char*, int sz);
private:
	MessageHandler messageHandler_;
	std::shared_ptr<EventLoop> eventLoop_;
	TcpServer* server_;
};

#endif

