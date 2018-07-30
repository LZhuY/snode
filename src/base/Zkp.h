#ifndef ZKP_H
#define ZKP_H

extern "C"{
	#include <zookeeper.h>
}

#include <map>
#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "App.h"

namespace SNODE{
	static struct String_vector svector;
	static char valbuff[1024];
	static const char* serverType = {"Hall", "Router", "DB"}

	void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx){
		std::cout << "watcher " << type << " " << state << " " << path << std::endl;
		Zkp* zkp = (Zkp*) watcherCtx;
		switch(type){
			case ZOO_SESSION_EVENT:
				zkp->onStateChange();
			case ZOO_CHILD_EVENT:
				zkp->onChildrenChange(path);
			case ZOO_DELETED_EVENT:
			case ZOO_CHANGED_EVENT:
		}
	}

	class ZKp{
	public:
		Zkp(std::string host, std::string path):host_(host), path_(path),state_(ZOO_CONNECTING_STATE){
			initZkp(host.c_str(), path.c_str());
		}

		void onChildrenChange(const char* path){
			std::map<std::string, std::string> tmpValues;
			zoo_wget_children(zh_, path, watcher, this, &svector);
			for(int i=0; i<svector.count; i++){
				std::string subPath = path;
				subPath.append("/");
				subPath.append(svector.data[i]);
				int len = 1024;
				int res = zoo_get(zh_, subPath.c_str(), 0, valbuff, &len, 0);
				if(len > 0)
					valbuff[len] = '\0';
				std::cout << subPath << " " << valbuff << std::endl;
				tmpValues.insert( std::pair<std::string, std::string>(subPath, std::string(valbuff)) );
			}

			std::map<std::string, std::string>& oldValues = values_[std::string(path)];
			for(auto iter=oldValues.begin(); iter!=oldValues.end(); ){
				if( tmpValues.find(iter->first) == tmpValues.end() ){
					// todo server offline
					App::getServer()->onServerOffline(iter->first, atoi(iter->second));
					iter = oldValues.erase(iter);
				}else
					iter++;
			}

			for(auto iter=tmpValues.begin(); iter=tmpValues.end(); iter++){
				if(oldValues.find(iter->first) == oldValues.end()){
					//todo server online
					App::getServer()->onServerOnline(iter->first, atoi(iter->second));
					oldValues.insert( std::pair<std::string, std::string>(iter->first, iter->second) );
				}
			}
		}

		void onStateChange(zhandle_t* zh, int stat){
			switch(state){
				case ZOO_CLOSED_STATE:
					reConnect();
				case ZOO_CONNECTED_STATE:
			}
		}

		void reConnect(){
			if(zh_ == NULL){
				zh_ = zookeeper_init(host, watcher, 30000, 0, this, 0);
			}
			for(int i=0; i<sizoef(serverType)/sizeof(char*); i++ )
				zoo_wget_children(zh_, serverType[i], watcher, this, &svector);
		}

		zhandle_t* initZkp(const char* host, const char* path){
			if(zh_ == NULL){
				zh_ = zookeeper_init(host, watcher, 30000, 0, this, 0);
			}
			for(int i=0; i<sizoef(serverType)/sizeof(char*); i++ )
				zoo_wget_children(zh_, serverType[i], watcher, this, &svector);
			return zh_;
		}

		void registerNode(zhandle_t* zh, const char* path, const char* value){
			char path_buff[1024];
			zoo_create(zh, path, value, strlen(value), &ZOO_OPEN_ACL_UNSAFE, 0, path_buff, 1024);
			std::cout << "registerNode " << path_buff << std::endl;
		}
	private:
		bool state_;
		zhandle_t* zh_;
		std::string host_;
		std::map<std::string, std::map<std::string, std::string>> values_;	
	};
}

#endif

/*
using namespace SNODE;

int main(int argc, char** argv){
	zhandle_t* zh = initZkp(argv[1], argv[2]);
	//registerNode(zh, "/Server/Hall/21001", "127.0.0.1:9881");
	int n =0;
	while(n<1000){
		sleep(5);
		n++;
	}
	return 0;
}

ZOO_CONNECTED_STATE
ZOO_CLOSED_STATE
ZOO_CONNECTING_STATE
*/