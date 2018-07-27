#ifndef HALL_H
#define HALL_H

#include "../base/Uncopy.h"

namespace SNODE{
	class Hall:public App {
	public:
		void start();
		void init();
		void loop();
		void fini();
		//void doZmqMsg();
		//void doNetMsg();
		void update();
	private:
		//int sid_;
	};
}

#endif