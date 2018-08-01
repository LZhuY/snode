#include "Router.h"
#include "../base/Buff.h"
#include "../base/ZmqNode.h"
#include "../base/Conf.h"
#include "../base/EpollLooper.h"
#include "../base/EventLoop.h"
#include "../base/Zkp.h"
#include "../base/Common.h"

extern "C"{
	#include <stdio.h>
}
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

		std::string zkHost = Conf::getConf()->getStr("zkHost");
		zkp_ = new ZKp(zkHost);

		char path[1024];
		snprintf(path, 1024, "/Router/%d", sid_);
		char myAddr[1024];
		snprintf(myAddr, 1024, "127.0.0.1:%d", port);
		zkp_->registerNode(path, myAddr);
		App::Self_ = this;
	}
	void Router::loop(){
		eventLoop_->loop();
	}
	void Router::fini(){
		//delete zmq_;
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
		MsgHead head;
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
	Conf::getConf()->setVal("sid", argv[2]);
	
	Router router;
	router.start();
}