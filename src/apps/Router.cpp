#include "Router.h"
#include "../base/ZmqNode.h"
#include "../base/Conf.h"

namespace SNODE{
	void Router::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
		
		if(zmq_ == NULL)
			zmq_ = new ZmqNode(ZMQ_ROUTER);
		const char* identity = "Router";
		zmq_->setOpt(ZMQ_IDENTITY, identity, strlen(identity));

		const char* addr = "tcp://127.0.0.1:8001";
		zmq_->bind(addr);
	}
	void Router::loop(){
		ZmqSock zmqsock;
	    zmqsock.iType = ZMQ_ROUTER;
	    zmqsock.sock = sock_;
		while(true){
			Zmqmsg zMsg;
			memset(&zMsg, 0, sizeof(zMsg));
			if(zmq_->recvMsg(zMsg)){
				zmq_->sendMsg(zMsg);
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

