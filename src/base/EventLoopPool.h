#ifndef _EVENTLOOPPOOL_H_
#define _EVENTLOOPPOOL_H_

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

namespace SNODE{

class EventLoop;

class EventLoopPool {
public:
	EventLoopPool(int threadNum);
	~EventLoopPool();

	std::shared_ptr<EventLoop>& getEventLoop();

private:
	int threadNum_;
	std::vector<std::thread*> threadPool_;
	std::vector<std::shared_ptr<EventLoop>> eventLoops_;
};
}

#endif