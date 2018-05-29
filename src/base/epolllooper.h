#ifndef EPOLL_LOOPER_H
#define EPOLL_LOOPER_H

#include "looper.h"
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <vector>
#include <map>

namespace SNODE{
extern const int MAX_EVENTS = 1024;

class Channel;
class Operator;

class EpollLooper: public Looper{
public:
	EpollLooper();
	~EpollLooper();

	void updateChannel(int oper, Channel*);
	std::vector<Channel*>& getActicityChannels();

private:
	std::map<Channel*> channels_;
	int epollfd_;
    struct epoll_event events_[MAX_EVENTS];
};
}
#endif