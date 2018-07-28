#include "Router.h"
#include "../base/ZmqNode.h"
#include "../base/Conf.h"

namespace SNODE{
	void Router::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
		std::string addr = Conf::getConf()->getStr("routerAddr");
		
		zmq_ = new ZmqNode(ZMQ_ROUTER);
		zmq_->setOpt(ZMQ_IDENTITY, &sid_, sizeof(sid_));
		zmq_->bind(addr.c_str());
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