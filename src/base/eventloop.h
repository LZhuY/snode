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
	typedef std::function<void()> DoInLoop;
	
	EventLoop(std::shared_ptr<Looper> looper, int threadNum);
	~EventLoop();
	void loop();
	void doInLoop(DoInLoop&& fun);
	EventLoop& getNextLoop();
	void doPenddingFuncs();
private:
	std::shared_ptr<Looper> looper_;
	std::vector<DoInLoop> pendingfuncs_;
	std::vector<EventLoop> looppool_;
	bool quit_;
	int threadsz_;
	std::mutex mutex_;
};

#endif