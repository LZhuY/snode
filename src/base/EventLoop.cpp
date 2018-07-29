#include "EventLoop.h"
#include "Channel.h"
#include "Looper.h"

namespace SNODE{
	EventLoop::EventLoop(int iNo):iNo_(iNo),looper_(NULL){ 
	};
	EventLoop::~EventLoop(){
		delete looper_;
	};

	int EventLoop::loop(){
		stop_ = false;
		std::vector<Channel*> activitys;
		while(!stop_){
			if(looper_ != NULL){
				looper_->getActivityChannels(activitys);
				for( std::vector<Channel*>::iterator iter = activitys.begin(); iter!=activitys.end();iter++ ){
					(*iter)->handlerEvent();
				}
			}
			activitys.clear();
			doPendingFunc();
			//std::cout << " EventLoop::loop() "<< iNo_ << std::endl;
			//break;
		}
		return 0;
	}

	void EventLoop::runInLoop(RunInLoopFun&& fun){
		RunInLoopFun func = std::move(fun);
		pendingFuncs_.push_back(func);
		std::cout << "runInLoop" << std::endl;
	}

	void EventLoop::doPendingFunc(){
		std::vector<RunInLoopFun> tmp = pendingFuncs_;
		pendingFuncs_.clear();
		for( std::vector<RunInLoopFun>::iterator iter=tmp.begin(); iter != tmp.end(); iter++ ){
			(*iter)();
		}
	}

	void EventLoop::setLooper(Looper* ptr){
		looper_ = ptr;
	}

	void EventLoop::addToLooper(int opr, Channel* ch){
		looper_->updateChannel(opr, ch);
	}
}