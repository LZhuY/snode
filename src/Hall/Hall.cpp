#include "../base/Conf.h"
#include "../base/EventLoop.h"
#include "../base/TcpServer.h"
#include "Hall.h"

#include <string>
#include <stdlib.h>

namespace SNODE{

	Hall::Hall(): App(), net_(NULL), zkp_(NULL){

	}

	void Hall::start(){
		init();
		loop();
		fini();
	}
	void Hall::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
		std::string addr = Conf::getConf()->getStr("MyAddr");
		int port = Conf::getConf()->getInt("ListenPort");

		eventLoop_ = new EventLoop(-1);
		eventLoop_->setLooper(new EpollLooper());
		net_ = new TcpServer(0);
		net_->setMessageHandler( std::bind(&Router::doNetMsg, this, std::placeholders::_1 ) );
		net_->setEventLoop(eventLoop_);
		net_->startListen(addr, port);

		std::string zkHost = Conf::getConf()->getStr("zkHost");
		zkp_ = new ZKp(zkHost);

		char path[1024];
		snprintf(path, 1024, "/%s/%d", type_.c_str(), sid_);
		char myAddr[1024];
		snprintf(myAddr, 1024, "%s:%d", addr.c_str(), port);
		zkp_->registerNode(path, myAddr);

		App::Self_ = this;
	}
	void Hall::loop(){

	}
	void Hall::fini(){

	}
	void Hall::update(){

	}

	void doZmqMsg(void* msg){

	}

	void doNetMsg(void* msg){

	}

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

		std::cout << "Hall onServerOnline " << sty << " " << sid << " " << ip << " " << port << std::endl;

		if(strcmp(sty, "Router"))
			net_->connect2Node(std::string(ip), atoi(port));
	}
	void onServerOffline(const char* path, const char* val){
		char sty[25];
		char sid[25];
		sscanf(path, "%[0-9a-z]/%[0-9a-z]", sty, sid);
		std::cout << " onServerOnline " << path << " " << val << std::endl;
	}
}

using namespace SNODE;

int main(int argc, char** argv){
	Conf::getConf()->setVal("sid", argv[1])
	Conf::getConf()->setVal("ListenPort", argv[2]);

	Hall hall;
	hall.start();
}