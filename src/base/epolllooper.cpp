#include "epolllooper.h"
#include "operator.h"
#include "log.h"

namespace SNODE{

extern const int EPOLL_ADD 0x0001;
extern const int EPOLL_DEL 0x0002;
extern const int EPOLL_MOD 0x0004;

EpollLooper::EpollLooper(std::string ip, int port){
	struct epoll_event ev;
	int listen_sock = socket();
	epollfd_ = epoll_create1(0);
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if (epoll_ctl(epollfd_, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
	   //exit(EXIT_FAILURE);
	}

}

void EpollLooper::updateChannel(int oper, Channel* ch){
	switch( oper ){
/*		case EPOLL_ADD:

		case EPOLL_DEL:
		case EPOLL_MOD:
		default:
			WRR("invalid oper");*/
		struct epoll_event ev;
		ev.events = EPOLLIN;
		if( (auto iter = channels_.find(ch->fd_)) != channels_.end())
			return;
		int s = epoll_ctl (epollfd_, oper, ch->fd_, &ev);
		if(s == 0)
			channels_[ch->fd_] = ch;
	}
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