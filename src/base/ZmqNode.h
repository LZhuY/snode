#ifndef ZMQNODE_H
#define ZMQNODE_H

#include <string.h>
#include <string>
#include <zmq.h>
#include <sys/epoll.h>
#include "Common.h"

namespace SNODE{
	class ZmqNode{
	public:
		ZmqNode(int itype);
		~ZmqNode();
		void addToLoop();
		int bind(const char* addr);
		int connect(const char* addr);
		void setOpt(int opt, const void* val, size_t sz);

		void setEventLoop(EventLoop* loop){eventLoop_ = loop;};

		void lock();
		void unlock();
		int sendMsg(Zmqmsg*);
		int recvMsg(Zmqmsg*);
		void onRecv();
	private:
		int itype_;
		void* ctx_;
		void* sock_;
		int fd_;
		EventLoop* eventLoop_;
	};
}

#endif