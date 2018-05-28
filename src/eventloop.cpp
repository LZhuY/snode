#include "eventloop.h"
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
		for(auto iter : activitys){
			(*iter)->evenHandler();
		}

		doPenddingFuncs();
	}	
}
void EventLoop::insert(std::function&& f){
	auto func = std::move(f);
	mutex_.locl();
	pendingfuncs_.push_back(func);
	mutex_.unlocl();
}

EventLoop& EventLoop::getNextLoop(){
	if(threadsz_ == 0)
		return *this;
	int r = rand()%threadsz_;
	return looppool_[r];
}

void EventLoop::doPenddingFuncs(){
	std::vector<std::function> funcs;
	mutex_.lock();
	funcs.swap(pendingfuncs_);
	mutex_.unlocl();
	for(auto func : funcs){
		(*func)();
	}
}
}