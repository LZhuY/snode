#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <memory>
#include <functional>
#include <iostream>
#include <string>

namespace SNODE{

const int MAX_BUFF_SIZE = 1024*16;

class Channel{
public:
	typedef std::function<void(int)> ErrorHandlerFunc;
	typedef std::function<void (Channel*, const char*, int)> MessageHandFunc;
	typedef std::function<void (int)> ConnectHandFunc;

	Channel(int fd):fd_(fd){  }

	void onRead(int fd);
	void onWrite(int fd);
	void writeToChannel(const char* buff, int sz);
	void handlerEvent();

	void setErrorHandler(ErrorHandlerFunc& func){ errorHandler_ = func;  }
	void setMessageHandFunc(MessageHandFunc& func){ messageHandFunc_ = func; }
	void setConnectHandFunc(ConnectHandFunc&& func){ connectHandFunc_ = std::move(func); }
	
private:
	int fd_;
	int event_; //事件类型
	unsigned char buff_[MAX_BUFF_SIZE];

	ErrorHandlerFunc errorHandler_;
	MessageHandFunc messageHandFunc_;
	ConnectHandFunc connectHandFunc_;
};

}
#endif