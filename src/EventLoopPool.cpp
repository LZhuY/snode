#include "EventLoopPool.h"
#include "EventLoop.h"

namespace SNODE{
	EventLoopPool::EventLoopPool(int threadNum):threadNum_(threadNum){ 
		for(int i=0;i<threadNum_;i++){
			std::shared_ptr<EventLoop> ptr(new EventLoop(i));
			eventLoops_.push_back( ptr );
			std::thread* th = new std::thread( std::bind(&EventLoop::loop, ptr) );
			threadPool_.push_back(th);
		}
	}
	EventLoopPool::~EventLoopPool(){
		for(int i=0;i<threadNum_;i++){
			threadPool_[i]->join();
		}
		return;
	}

	std::shared_ptr<EventLoop>& EventLoopPool::getEventLoop(){
		int r = rand()%threadNum_;
		return eventLoops_[r];
		//return std::shared_ptr<EventLoop>(new EventLoop(0));
	}
}