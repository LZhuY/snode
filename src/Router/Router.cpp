#include "Router.h"
#include "../base/ZmqNode.h"
#include "../base/Conf.h"
#include <iostream>

namespace SNODE{
	void Router::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
		zmq_ = new ZmqNode(ZMQ_ROUTER);

		const char* identity = "Router";
		zmq_->setOpt(ZMQ_IDENTITY, identity, strlen(identity));

		const char* addr = "tcp://127.0.0.1:8001";
		zmq_->bind(addr);
	}
	void Router::loop(){
		while(true){
			Zmqmsg zMsg;
			memset(&zMsg, 0, sizeof(zMsg));
			if(zmq_->recvMsg(&zMsg)){
				zmq_->sendMsg(&zMsg);
				memset(&zMsg, 0, sizeof(zMsg));
			}
		}
	}
	void Router::fini(){
		delete zmq_;
	}
	void Router::start(){
		init();
		loop();
		fini();
	}
	/*void Router::doZmqMsg(){

	}*/
	void Router::update(){

	}
}


using namespace SNODE;

int main(int argc, char** argv){
	Conf::getConf()->setVal("port", argv[1]);
	
	Router router;
	router.start();
}