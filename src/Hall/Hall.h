#ifndef HALL_H
#define HALL_H

#include "../base/App.h"


namespace SNODE{
	class TcpServer;
	class ZKp;

	class Hall:public App {
	public:
		Hall();
		void start();
		void init();
		void loop();
		void fini();
		void doZmqMsg(void* msg);
		void doNetMsg(void* msg);
		void update();

		void onServerOnline(const char* path, const char* val);
		void onServerOffline(const char* path, const char* val);
	private:
		TcpServer* net_;
		ZKp* zkp_;
	};
}

#endif