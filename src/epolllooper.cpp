#include "epolllooper.h"
#include "operator.h"
#include "log.h"

extern const int EPOLL_ADD 0x0001;
extern const int EPOLL_DEL 0x0002;
extern const int EPOLL_MOD 0x0004;

void EpollLooper::updateChannel(int oper, Channel&){
	switch( oper ){
		case EPOLL_ADD:
		case EPOLL_DEL:
		case EPOLL_MOD:
		default:
			WRR("invalid oper");
	}
}
std::vector<Channel>& EpollLooper::getActicityChannels(){
	
}