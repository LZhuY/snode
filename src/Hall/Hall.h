#ifndef HALL_H
#define HALL_H

#include "../base/App.h"

namespace SNODE{
	class Hall:public App {
	public:
		Hall():App(){}
		void start();
		void init();
		void loop();
		void fini();
		//void doZmqMsg(void* msg);
		//void doNetMsg(void* msg);
		void update();
	private:
		//int sid_;
	};
}

#endif