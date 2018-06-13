#include "Looper.h"
#include <vector>

#ifndef _EPOLLLOPER_H_
#define _EPOLLLOPER_H_
namespace SNODE{
class Looper;
class Channel;

class EpollLooper : public Looper{
public:
	void updateChannel(int oper, Channel*);
	std::vector<Channel*> getActivityChannels();
};
}
#endif