#ifndef LOOPER_H
#define LOOPER_H

#include <vector>

namespace SNODE{

class Channel;

class Looper{
public:
	//Looper();
	//virtual ~Looper()=0;
	virtual void updateChannel(int, Channel*)=0;
	virtual std::vector<Channel*> getActicityChannels()=0;
private:
	//std::vector<Channel> channels_;
};

}
#endif