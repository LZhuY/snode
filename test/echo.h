#ifndef _ECHO_H_
#define _ECHO_H_

#include "../src/base/TcpServer.h"
#include "../src/base/EventLoop.h"

using namespace SNODE;

class SNODE::Buff;

class Echo {
public:
	typedef std::function<void(Channel*, SNODE::Buff& , int sz)> MessageHandler;

	Echo(){}
	~Echo(){}

	void setEventLoop(std::shared_ptr<EventLoop>& loop);
	void setTcpServer(TcpServer* server);
	void setMessageHandler(MessageHandler&& func);
	void onMessageHandler(Channel*, SNODE::Buff&, int sz);
private:
	MessageHandler messageHandler_;
	std::shared_ptr<EventLoop> eventLoop_;
	TcpServer* server_;
};

#endif

