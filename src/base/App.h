#ifndef APP_H
#define APP_H

#include "../base/Uncopy.h"
#include <string>

namespace SNODE{
	class App : public Uncopy{
	public:
		App():Uncopy(){}
		virtual void start()=0;
		virtual void init()=0;
		virtual void loop()=0;
		virtual void fini()=0;
		virtual void doZmqMsg(){};
		virtual void doNetMsg(){};
		virtual void update()=0;
	protected:
		int sid_;
		std::string type_;
	};
}

#endif