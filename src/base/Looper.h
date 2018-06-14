#ifndef _LOOPER_H
#define _LOOPER_H

#include <vector>

namespace SNODE{

class Channel;

class Looper{
public:
	virtual ~Looper(){}
	virtual void updateChannel(int oper, Channel*)=0;
	virtual void getActivityChannels(std::vector<Channel*>&)=0;
};

}
#endif