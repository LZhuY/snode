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
		std::string addr = Conf::getConf()->getStr("listenAddr");
		int port = Conf::getConf()->getInt("port");
		
		//zmq_ = new ZmqNode(ZMQ_ROUTER);
		//zmq_->setOpt(ZMQ_IDENTITY, &sid_, sizeof(sid_));
		//zmq_->bind(addr.c_str());
		
		eventLoop_ = new EventLoop(-1);
		eventLoop_->setLooper(new EpollLooper());
		net_ = new TcpServer(0);
		net_->setMessageHandler( std::bind(&Router::doNetMsg, this, std::placeholders::_1 ) );
		net_->setEventLoop(eventLoop_);
		net_->startListen(addr, port);
	}
	void Router::loop(){
		eventLoop_->loop();
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
		Buff& buff = *((Buff*)msg);
		Head head;
		buff << head.sid << head.fid << head.coid << head.eid << head.ssn ;
		if(head.sid == sid_){

		}else{
			
		}
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