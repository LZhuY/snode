#ifndef CONTEXT_H
#define CONTEXT_H
namespace SNODE{

class Message;
class Context{
	virtual void parse(const char* buff)=0;
	virtual bool isComplete()=0;
	virtual Message* getMessage()=0;
};
}

#endif