#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <vector>
#include <functional>
#include <memory>

class Looper;

class EventLoop{
public:
	EventLoop(std::shared_ptr<Looper> looper, int threadNum);
	~EventLoop();
	void loop();
	void insert(std::function&& fun);
	EventLoop& getNextLoop();
private:
	std::shared_ptr<Looper> looper_;
	std::vector<function> pendingfuncs_;
	std::vector<EventLoop> looppool_;
	bool quit_;
	int threadsz_;
};

#endif