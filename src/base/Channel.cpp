#include "Looper.h"
#include "Channel.h"
#include <iostream>
#include <sys/epoll.h>

namespace SNODE{
	void Channel::handlerEvent(){
		std::cout<< "Channel::handlerEvent" << std::endl;
		if(isListen()){
			std::cout << "isListen" << std::endl;
			int fd = accept(fd_, (struct sockaddr*)NULL, NULL);
			socket_non_blocking(fd);
			connectHandFunc_(fd);
		}else{
			if(events_ &  EPOLLIN){
				if(onReadMssage_){
					onReadMssage_();
					return;
				}
				int n = recv(fd_, cache_, MAX_BUFF_SIZE, 0);
				buff_.append(cache_, n);

				std::cout << buff_.data() << " " << n << std::endl;
				if( buff_.isComplete()){
					std::cout << "complete" << std::endl;
					messageHandFunc_((void*)&buff_);
				}
				else{
					//std::cout << "disconnet" << std::endl;
				}
			}else if(events_ & EPOLLOUT){
				onWrite();
			}

		}
	}

	void Channel::onWrite(){
		
	}

	void Channel::writeToChannel(const char* buff, int sz){
		std::cout << buff << " " << sz << std::endl;
		send(fd_, buff, 1, sz);
	}
}