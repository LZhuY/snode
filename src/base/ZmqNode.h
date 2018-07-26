#ifndef ZMQNODE_H
#define ZMQNODE_H

#include <zmq.h>
#include "Common.h"

namespace SNODE{
	class ZmqNode{
	public:
		ZmqNode(int itype);
		~ZmqNode();
		int bind(std::stirng& addr);
		int connect(std::string& addr);
		void setOpt(int opt, const void* val, int sz);

		void lock();
		void unlock();
		int sendMsg(Zmqmsg&);
		int recvMsg(Zmqmsg&);
	private:
		int itype_;
		void* ctx_;
		void* sock_;
	};
}

#endif