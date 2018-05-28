#ifndef LOOPER_H
#define LOOPER_H

#include <vecotr>

namespace SNODE{

class Channel;

class Looper{
public:
	Looper();
	virtual Looper();
	virtual void updateChannel(Channel*);
	virtual std::vector<Channel*>& getActicityChannels();
private:
	//std::vector<Channel> channels_;
};

}
#endif