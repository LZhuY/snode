#include "Router.h"
#include "../base/Buff.h"
#include "../base/ZmqNode.h"
#include "../base/Conf.h"
#include "../base/EpollLooper.h"
#include "../base/EventLoop.h"
#include <iostream>

namespace SNODE{
	void Router::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
		std::string addr = Conf::getConf()->getStr("routerAddr");
		int port = Conf::getConf()->getInt("port");
		
		zmq_ = new ZmqNode(ZMQ_ROUTER);
		zmq_->setOpt(ZMQ_IDENTITY, &sid_, sizeof(sid_));
		zmq_->bind(addr.c_str());
		
		eventLoop_ = new EventLoop(-1);
		eventLoop_->setLooper(new EpollLooper());
		net_ = new TcpServer(0);
		net_->setEventLoop(eventLoop_);
		net_->startListen(std::string("127.0.0.1"), port);
		//net_->setMessageHandler( std::bind(&Router::doNetMsg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ) );
	}
	void Router::loop(){
		while(true){
			Zmqmsg zMsg;
			memset(&zMsg, 0, sizeof(zMsg));
			if(zmq_->recvMsg(&zMsg)){
				std::cout << "recvMsg" << std::endl;
				zmq_->sendMsg(&zMsg);
				memset(&zMsg, 0, sizeof(zMsg));
			}
			eventLoop_->loop();
		}
	}
	void Router::fini(){
		delete zmq_;
		delete net_;
		delete eventLoop_;
	}
	void Router::start(){
		init();
		loop();
		fini();
	}

	void Router::doZmqMsg(void* msg){

	}
	void Router::doNetMsg(void* msg){
		//Buff* buff = (Buff*)msg;
		//std::cout << buff->data() << std::endl;
	}

	void Router::update(){

	}
}


using namespace SNODE;

int main(int argc, char** argv){
	Conf::getConf()->setVal("port", argv[1]);
	
	Router router;
	router.start();
}