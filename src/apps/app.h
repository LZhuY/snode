#ifndef APP_H
#define APP_H

#include "../base/Uncopy.h"

namespace SNODE{
	class App : public Uncopy{
	public:
		virtual void start()=0;
		virtual void init()=0;
		virtual void loop()=0;
		virtual void fini()=0;
		virtual void doMsg()=0;
		virtual void update()=0;
	};
}

#endif