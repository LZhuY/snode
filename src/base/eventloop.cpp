#include "eventloop.h"
#include "channel.h"
#include "looper.h"

namespace SNODE{

EventLoop::EventLoop(std::shared_ptr<Looper> looper, int threadNum):looper_(looper),threadsz_(threadNum){
	if(threadNum > 0){
		for(int i=0; i<threadNum; i++)
			looppool_.push_back( new EventLoop(looper, 0) );
	}
}
EventLoop::~EventLoop(){
/*	for(auto fun : pendingfuncs_){

	}*/
}
void EventLoop::loop(){
	while(true){
		if(quit_) break;

		std::vector<Channel*>& activitys = looper_->getActicityChannels();
		for(auto iter =activitys.begin(); iter!=activitys.end(); iter++){
			(*iter)->evenHandler();
		}

		doPenddingFuncs();
	}	
}
void EventLoop::doInLoop(LoopFunc&& f){
	auto func = std::move(f);
	mutex_.lock();
	pendingfuncs_.push_back(func);
	mutex_.unlock();
}

EventLoop& EventLoop::getNextLoop(){
	if(threadsz_ == 0)
		return *this;
	int r = rand()%threadsz_;
	return looppool_[r];
}

void EventLoop::doPenddingFuncs(){
	std::vector<LoopFunc> funcs;
	mutex_.lock();
	funcs.swap(pendingfuncs_);
	mutex_.unlock();
	for(auto iter=funcs.begin(); iter!=funcs.end(); iter++){
		(*iter)();
	}
}
}