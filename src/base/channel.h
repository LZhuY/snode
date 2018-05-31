#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include "context.h"
#include <functional>
#include <sys/types.h>
#include <fcntl.h>

extern const int MAX_LINE = 1024;
 
namespace SNODE{

bool SetSocketBlockingEnabled(int fd)
{
   if (fd < 0) return false;
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags == -1) return false;
   flags = (flags | O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
}


class Channel{
public:
	typedef std::function<void (const char*, int len, Channel*)> ReadFunc;
	typedef std::function<void (int)> ConnectFunc;

	Channel(int fd);
	~Channel();

	void setReadFunc(ReadFunc&& func);
	//void setWriteFunc(std::function&& func);
	void setConnFunc(ConnectFunc&& func);
	//void setContext(std::shared_ptr<Context> context);

	void onRead();
	void onConn(int fd);
	void onWrite();

	bool writeToChannel(const char* buff, int sz);
	bool isListen(){ return islisten_; };
	void evenHandler();
	void listenChannel(std::string ip, int port);
private:
	int fd_;
	ReadFunc readhandler_;
	//std::function<void (Channel&)> writehandler_;
	ConnectFunc connhandler_;
	char inbuff_[MAX_LINE];
	char outbuff_[MAX_LINE];

	int loutpos_;
	int routpos_;

	int linpos_;
	int rinpos_;

	int revents_;
	bool islisten_;

	//std::shared_ptr<Context> context_;

	//std::function<void (const Message*)> readhandler_;
};
}
#endif