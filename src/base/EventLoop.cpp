#include "EventLoop.h"
#include "Channel.h"
#include "Looper.h"

namespace SNODE{
	EventLoop::EventLoop(int iNo):iNo_(iNo),looper_(NULL){ 
	};
	EventLoop::~EventLoop(){
		
	};

	int EventLoop::loop(){
		stop_ = false;
		while(!stop_){
			if(looper_ != NULL){
				std::vector<Channel*> activitys = looper_->getActivityChannels();
				for(auto ch : activitys){
					ch->handlerEvent();
				}
			}

			doPendingFunc();
			std::cout << " EventLoop::loop() "<< iNo_ << std::endl;
			break;
		}
		return 0;
	}

	void EventLoop::runInLoop(RunInLoopFun&& fun){
		RunInLoopFun func = std::move(fun);
		pendingFuncs_.push_back(func);
	}

	void EventLoop::doPendingFunc(){
		std::vector<RunInLoopFun> tmp = pendingFuncs_;
		pendingFuncs_.clear();
		for(auto func : tmp){
			func();
		}
	}

	void EventLoop::setLooper(Looper* ptr){
		looper_ = ptr;
	}

	void EventLoop::addToLooper(int opr, Channel* ch){
		looper_->updateChannel(opr, ch);
	}
}