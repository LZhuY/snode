#ifndef _LOOPER_H
#define _LOOPER_H

#include <vector>

namespace SNODE{

class Channel;

class Looper{
public:
	virtual ~Looper(){}
	virtual void updateChannel(int oper, Channel*)=0;
	virtual std::vector<Channel*> getActivityChannels()=0;
};

}
#endif