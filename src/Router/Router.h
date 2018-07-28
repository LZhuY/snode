#ifndef ROUTER_H
#define ROUTER_H

#include "../base/App.h"

namespace SNODE{
	class ZmqNode;
	class Router : public App{
	public:
		Router():App(){}
		void start();
		void init();
		void loop();
		void fini();
		//void doZmqMsg();
		//void doNetMsg();
		void update();
	private:
		ZmqNode* zmq_;
		//int sid_;
	};
}

#endif