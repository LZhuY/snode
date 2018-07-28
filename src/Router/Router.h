#ifndef ROUTER_H
#define ROUTER_H

#include "../base/App.h"
#include "../base/TcpServer.h"

namespace SNODE{
	class EventLoop;
	class EpollLooper;
	class ZmqNode;
	class Router : public App{
	public:
		Router():App(){}
		void start();
		void init();
		void loop();
		void fini();
		void doZmqMsg(void* msg);
		void doNetMsg(void* msg);
		void update();
	private:
		EventLoop* eventLoop_;
		EpollLooper* epollLooper_;
		ZmqNode* zmq_;
		TcpServer* net_;
		//int sid_;
	};
}

#endif