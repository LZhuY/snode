#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <vector>
#include <functional>
#include <memory>
#include <thread>         
#include <mutex>          

class Looper;

class EventLoop{
public:
	EventLoop(std::shared_ptr<Looper> looper, int threadNum);
	~EventLoop();
	void loop();
	void insert(std::function&& fun);
	EventLoop& getNextLoop();
	void doPenddingFuncs();
private:
	std::shared_ptr<Looper> looper_;
	std::vector<function> pendingfuncs_;
	std::vector<EventLoop> looppool_;
	bool quit_;
	int threadsz_;
	std::mutex mutex_;
};

#endif