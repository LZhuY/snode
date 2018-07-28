#include "../base/Conf.h"
#include "Hall.h"

namespace SNODE{
	void Hall::start(){
		init();
		loop();
		fini();
	}
	void Hall::init(){
		sid_ = Conf::getConf()->getInt("sid");
		type_ = Conf::getConf()->getStr("type");
	}
	void Hall::loop(){

	}
	void Hall::fini(){

	}
	void Hall::update(){

	}

	//void doZmqMsg();
	//void doNetMsg();
}

using namespace SNODE;

int main(int argc, char** argv){
	Conf::getConf()->setVal("port", argv[1]);

	Hall hall;
	hall.start();
}