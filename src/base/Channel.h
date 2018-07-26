#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "Buff.h"
#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <fcntl.h>

namespace SNODE{

static int socket_non_blocking(int sfd)
{  
	int flags, s;
	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1)
	{  
		return -1;
	}
	flags |= O_NONBLOCK;
	s = fcntl (sfd, F_SETFL, flags);
	if (s == -1)
	{
		return -1;
	}
	return 0;
}

const int MAX_BUFF_SIZE = 1024*16;

class Buff;

class Channel{
public:
	typedef std::function<void(int)> ErrorHandlerFunc;
	typedef std::function<void (Channel*, Buff&, int)> MessageHandFunc;
	typedef std::function<void (int)> ConnectHandFunc;

	Channel(int fd, bool isListen=false):fd_(fd),isListen_(isListen){  }

	//void onRead(int fd);
	void onWrite();
	void writeToChannel(const char* buff, int sz);
	void handlerEvent();
	bool isListen(){ return isListen_; }

	void setErrorHandler(ErrorHandlerFunc& func){ errorHandler_ = func;  }
	void setMessageHandFunc(MessageHandFunc& func){ messageHandFunc_ = func; }
	void setConnectHandFunc(ConnectHandFunc&& func){ connectHandFunc_ = std::move(func); }
	int fd_;
	int events_; //
private:
	bool isListen_;
	char cache_[MAX_BUFF_SIZE];
	Buff buff_;
	ErrorHandlerFunc errorHandler_;
	MessageHandFunc messageHandFunc_;
	ConnectHandFunc connectHandFunc_;
};

}
#endif