#ifndef ROUTER_H
#define ROUTER_H

#include "../base/App.h"
#include "../base/TcpServer.h"
#include <stdlib.h>

namespace SNODE{
	class ZKp;
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

		void onServerOnline(const char* path, const char* val){

			std::cout << "Router onServerOnline " << path << " " << val << std::endl;

			char sty[25];
			char sid[25];
			sscanf(path, "/%[0-9a-zA-Z]/%[0-9]", sty, sid);

			if(atoi(sid) == sid_){
				return;
			}

			char ip[25];
			char port[8];

			sscanf(val, "%[^:]:%[0-9]", ip, port);

			std::cout << "Router onServerOnline " << sty << " " << sid << " " << ip << " " << port << std::endl;

			net_->connect2Node(std::string(ip), atoi(port));
		}
		void onServerOffline(const char* path, const char* val){
			char sty[25];
			char sid[25];
			sscanf(path, "%[0-9a-z]/%[0-9a-z]", sty, sid);
			std::cout << " onServerOnline " << path << " " << val << std::endl;
		}

	private:
		EventLoop* eventLoop_;
		EpollLooper* epollLooper_;
		ZmqNode* zmq_;
		TcpServer* net_;
		ZKp* zkp_;
		//int sid_;
	};
}

#endif