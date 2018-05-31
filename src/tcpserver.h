#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>
#include <memory>

#include "base/eventloop.h"
#include "base/epolllooper.h"
#include "base/server.h"

namespace SNODE{

class Message;
class Channel;

class TcpServer: public Server{
public:
	typedef std::function<void (Message*)> MessageHandler;
	typedef std::function<void (Channel*)> ConnectHandler;
	//typedef std::function<void (const char*)> ReadHandler;

	TcpServer(std::shared_ptr<EventLoop> loop, std::string ip, int port);
	void onConn(int fd);
	void onRead(const char* buff, int sz, Channel* ch);
	void start();
	void stop();

	void setMessageHandler(MessageHandler&& func);
	void setConnectHandler(ConnectHandler&& func);
	//void setReadHandler(ReadHandler&& func);
private:
	std::shared_ptr<EventLoop> eventLoop_;
	MessageHandler messageHandler_;
	ConnectHandler connectHandler_;
	int port_;
	std::string ip_;
	//ReadHandler    readHandler_;
};

}
#endif