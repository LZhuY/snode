#ifndef APP_H
#define APP_H

#include "../base/Uncopy.h"
extern "C"{
	#include <cstdlib>
}
#include <string>
#include <iostream>

namespace SNODE{
	class App;
	class App : public Uncopy{
	public:
		App():Uncopy(){}
		virtual void start()=0;
		virtual void init()=0;
		virtual void loop()=0;
		virtual void fini()=0;
		virtual void doZmqMsg(void* msg){}
		virtual void doNetMsg(void* msg){}
		virtual void update()=0;

		virtual void onServerOnline(const char* path, const char* val){
			char sty[25];
			char sid[25];
			sscanf(path, "%[0-9a-z]/%[0-9a-z]", sty, sid);
			std::cout<< sty << " " << sid << " " << val << std::endl;
		}
		virtual void onServerOffline(const char* path, const char* val){
			char sty[25];
			char sid[25];
			sscanf(path, "%[0-9a-z]/%[0-9a-z]", sty, sid);
			std::cout<< sty << " " << sid << " " << val << std::endl;
		}
		static App* getServer(){ return Self_; }
		static App* Self_;
	protected:
		int sid_;
		std::string type_;
	};
	App* App::Self_ = 0;
}

#endif