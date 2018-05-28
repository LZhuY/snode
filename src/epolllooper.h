#ifndef EPOLL_LOOPER_H
#define EPOLL_LOOPER_H

#include "looper.h"

class Channel;
class Operator;

class EpollLooper: public Looper{
public:
	EpollLooper();
	~EpollLooper();

	void updateChannel(int oper, Channel&);
	std::vector<Channel>& getActicityChannels();

private:
	std::vector<Channel> channels_;
};

#endif