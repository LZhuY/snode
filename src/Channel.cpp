#include "Looper.h"
#include "Channel.h"
#include <iostream>

namespace SNODE{
	void Channel::handlerEvent(){
		std::cout<< "Channel::handlerEvent" << std::endl;
		//switch(event_){
		//case 1:
		//default:
		//}
	}

	void Channel::onRead(int fd){
		if(messageHandFunc_ != NULL){
			std::string msg("this is a message");
			messageHandFunc_(this, msg.c_str(), msg.size());
		}
	}

	void Channel::onWrite(int fd){
	
	}

	void Channel::writeToChannel(const char* buff, int sz){
		std::cout << buff << " " << sz << std::endl;
	}
}