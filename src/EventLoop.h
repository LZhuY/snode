#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_

#include "EventLoopPool.h"

#include <vector>
#include <memory>
#include <functional>

namespace SNODE{

class Looper;
class Channel;

class EventLoop{
public:
	EventLoop(int iNo);
	virtual ~EventLoop();
	typedef std::function<void()>  RunInLoopFun;
	int loop();
	void runInLoop(RunInLoopFun&& fun);
	void doPendingFunc();
	void setLooper(Looper* ptr);
	void addToLooper(int, Channel*);
private:
	Looper* looper_;
	std::vector<RunInLoopFun> pendingFuncs_;
	bool stop_;
	int iNo_;
};

}

#endif