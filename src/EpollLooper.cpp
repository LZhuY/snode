#include "EpollLooper.h"
#include "Channel.h"

namespace SNODE{

void EpollLooper::updateChannel(int opr, Channel* ch){
	
}

std::vector<Channel*> EpollLooper::getActivityChannels(){
	std::vector<Channel*> chs;
	return chs;
};

}