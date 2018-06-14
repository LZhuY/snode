#ifndef _EPOLLLOPER_H_
#define _EPOLLLOPER_H_

#include <sys/socket.h>  
#include <netdb.h>  
#include <fcntl.h>  
#include <sys/epoll.h>
#include <string.h> 
#include "Looper.h"
#include <vector>
#include <map>

namespace SNODE{
class Looper;
class Channel;
const int MAX_EVENT_NUM = 1024;

class EpollLooper : public Looper{
public:
	EpollLooper();
	void updateChannel(int oper, Channel*);
	void getActivityChannels(std::vector<Channel*>&);
private:
	int efd_;
	std::map<int, Channel*> channels_;
	struct epoll_event events_[MAX_EVENT_NUM];
};
}
#endif