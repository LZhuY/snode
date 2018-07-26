#ifndef ROUTER_H
#define ROUTER_H

#include "../base/App.h"

namespace SNODE{
	class Router : public App{
	public:
		void start();
		void init();
		void loop();
		void fini();
		void doMsg();
		void update();
	private:
		ZmqNode* zmq_;
		int sid_;
	};
}

#endif