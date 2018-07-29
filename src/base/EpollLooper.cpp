#include "EpollLooper.h"
#include "Channel.h"
#include <iostream>

namespace SNODE{

EpollLooper::EpollLooper(){
	efd_ = epoll_create1(0);
	if(efd_ == -1){
		std::cout<< "epoll create error" << std::endl;
	}
}

void EpollLooper::updateChannel(int opr, Channel* ch){
	struct epoll_event event;
	event.data.fd = ch->fd_;
	event.events =  EPOLLIN | EPOLLET;
	int res = epoll_ctl(efd_, ch->events_ , ch->fd_, &event); //EPOLL_CTL_ADD
	if(res == -1){
		std::cout << "epoll ctl error" << std::endl;
	}
	std::cout << "updateChannel 111" << ch->events_ << std::endl;
	channels_.insert( std::make_pair(ch->fd_, ch) );
	std::cout << "updateChannel 222" << ch->events_ << std::endl;
}

void EpollLooper::getActivityChannels(std::vector<Channel*>& channels){
	int n = epoll_wait(efd_, events_, MAX_EVENT_NUM, 0);
	if(n > 0 ){
		std::cout << " epoll wait " << n << std::endl;
		for(int i=0;i<n;i++){
			int fd = events_[i].data.fd;
			auto iter = channels_.find(fd);
			if(iter != channels_.end()){
				Channel* ch = iter->second;
				ch->events_ = events_[i].events;
				channels.push_back(ch);
			}
		}
	}
};

}