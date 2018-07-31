#ifndef ZKP_H
#define ZKP_H

extern "C"{
	#include <zookeeper.h>
}

#include <iostream>
#include <string.h>

namespace SNODE{
	static struct String_vector svector;
	char valbuff[1024];

	void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx){
		std::cout << "watcher " << type << " " << state << " " << path << std::endl;
		zoo_wget_children(zh, path, watcher, 0, &svector);
		for(int i=0; i<svector.count; i++){
			std::string subPath = path;
			subPath.append("/");
			subPath.append(svector.data[i]);
			int len = 1024;
			int res = zoo_get(zh, subPath.c_str(), 0, valbuff, &len, 0);
			if(len > 0)
				valbuff[len] = '\0';
			std::cout << subPath << " " << valbuff << std::endl;
		}
	}

	zhandle_t* initZkp(const char* host, const char* path){
		zhandle_t* zh = zookeeper_init(host, watcher, 30000, 0, 0, 0);
		if(zh == NULL){
			std::cout << "zookeeper init error" << std::endl;
			return zh;
		}
		zoo_wget_children(zh, path, watcher, 0, &svector);
		return zh;
	}

	void registerNode(zhandle_t* zh, const char* path, const char* value){
		char path_buff[1024];
		zoo_create(zh, path, value, strlen(value), &ZOO_OPEN_ACL_UNSAFE, 0, path_buff, 1024);
		std::cout << "registerNode " << path_buff << std::endl;
	}

	void dispatch(int event, const char* path, const char* value){

	}
};

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
*/