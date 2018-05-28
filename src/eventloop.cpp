#include "eventloop.h"

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
	}
}
void insert(std::function&& fun);

EventLoop& EventLoop::getNextLoop(){
	if(threadsz_ == 0)
		return *this;
	int r = rand()%threadsz_;
	return looppool_[r];
}