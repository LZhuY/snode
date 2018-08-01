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
	static const char* serverType[] = {"/Hall", "/Router", "/DB"};
	void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx);

	class ZKp{
	public:
		ZKp(std::string host):zh_(NULL),host_(host),state_(ZOO_CONNECTING_STATE){
			initZkp(host.c_str());
		}

		void onChildrenChange(const char* path){
			std::map<std::string, std::string> tmpValues;
			zoo_wget_children(zh_, path, watcher, this, &svector);
			for(int i=0; i<svector.count; i++){
				std::string subPath = std::string(path);
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
					App::getServer()->onServerOffline(iter->first.c_str(), iter->second.c_str());
					oldValues.erase(iter++);
				}else
					iter++;
			}

			for(auto iter=tmpValues.begin(); iter!=tmpValues.end(); iter++){
				if(oldValues.find(iter->first) == oldValues.end()){
					//todo server online
					App::getServer()->onServerOnline(iter->first.c_str(), iter->second.c_str());
					oldValues.insert( std::pair<std::string, std::string>(iter->first, iter->second) );
				}
			}
		}

		void onStateChange(int stat){
			/*if(stat == ZOO_CLOSED_STATE)
			{
				reConnect();
			}else if(stat == ZOO_CONNECTED_STATE){
				std::cout << "ZOO_CONNECTED_STATE" << std::endl;
			}*/
			reConnect();
		}

		void reConnect(){
			if(zh_ == NULL){
				zh_ = zookeeper_init(host_.c_str(), watcher, 30000, 0, this, 0);
			}
			for(int i=0; i<sizeof(serverType)/sizeof(char*); i++ )
				zoo_wget_children(zh_, serverType[i], watcher, this, &svector);
		}

		zhandle_t* initZkp(const char* host){
			if(zh_ == NULL){
				zh_ = zookeeper_init(host, watcher, 30000, 0, this, 0);
			}
			for(int i=0; i<sizeof(serverType)/sizeof(char*); i++ )
				zoo_wget_children(zh_, serverType[i], watcher, this, &svector);
			return zh_;
		}

		void registerNode(const char* path, const char* value){
			std::cout << " registerNode " << path << " " << value << std::endl;
			char path_buff[1024];
			zoo_create(zh_, path, value, strlen(value), &ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL, path_buff, 1024);
			//std::cout << "registerNode " << path_buff << std::endl;
		}
	private:
		bool state_;
		zhandle_t* zh_;
		std::string host_;
		std::map<std::string, std::map<std::string, std::string>> values_;	
	};

	void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx){
		std::cout << "watcher watcher " << type << " " << state << " " << path << std::endl;
		ZKp* zkp = (ZKp*) watcherCtx;
		if(type == ZOO_SESSION_EVENT){
			zkp->onStateChange(state);
		}else if(type == ZOO_CHILD_EVENT){
			zkp->onChildrenChange(path);
		}
	}
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