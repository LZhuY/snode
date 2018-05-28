#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>
#include "context.h"
#include <functional>

extern const int MAX_LINE = 1024;
extern const int 
namespace SNODE{
class Channel{
public:
	std::function<void (const char*, int len)> ReadFunc;
	std::function<void (int)> ConnectFunc;

	Channel(int fd);
	~Channel();

	void setReadFunc(ReadFunc&& func);
	//void setWriteFunc(std::function&& func);
	void setConnFunc(ConnectFunc&& func);
	//void setContext(std::shared_ptr<Context> context);

	void onRead();
	void onConn(int fd);
	void onWrite();

	bool write(const char* buff, int sz);
	bool isListen(){ return islisten_; };
	void evenHandler();
private:
	int fd_;
	ReadFunc readhandler_;
	//std::function<void (Channel&)> writehandler_;
	std::function<void (int fd)> connhandler_;
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