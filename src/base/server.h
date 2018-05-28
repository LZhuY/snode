#ifndef SERVER_H
#define SERVER_H
namespace SNODE{

class Server{
	virtual void start() = 0;
	virtual void stop() = 0;
};

}

#endif