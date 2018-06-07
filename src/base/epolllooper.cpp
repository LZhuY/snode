#include "epolllooper.h"
#include "operator.h"
#include "log.h"

namespace SNODE{

EpollLooper::~EpollLooper(){
/*	for(auto iter : channels_){
		iter->second
	}*/
}

EpollLooper::EpollLooper(){

}

void EpollLooper::updateChannel(int oper, Channel* ch){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	if( channels_.find(ch->fd_) != channels_.end())
		return;
	int s = epoll_ctl(epollfd_, oper, ch->fd_, &ev);
	if(s == 0)
		channels_[ch->fd_] = ch;
}

std::vector<Channel*>& EpollLooper::getActicityChannels(){
	int nfds = epoll_wait(epollfd_, events_, MAX_EVENTS, -1);
	std::vector<Channel*> tmp;
	Channel* ch = nullptr;
	for(int i=0; i<nfds; i++){
		int fd = events_[i].data.fd;
		auto iter = channels_.find(fd);
		if(iter != channels_.end()){
			ch = *(iter->second);
			ch->revents_ = events_[i].events;
			tmp.push_back(ch);
		}
	}
	return tmp;
}
}