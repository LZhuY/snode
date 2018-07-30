#ifndef ZKP_H
#define ZKP_H

extern "C"{
	#include <zookeeper.h>
}

#include <iostream>
#include <string.h>

namespace SNODE{
	static struct String_vector svector;
	static const char* Path = "/Server";

	void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx){
		std::cout << "watcher " << type << " " << state << " " << path << std::endl;
		zoo_wget_children(zh, Path, watcher, 0, &svector);
	}

	zhandle_t* initZkp(const char* host){
		zhandle_t* zh = zookeeper_init(host, watcher, 30000, 0, 0, 0);
		if(zh == NULL){
			std::cout << "zookeeper init error" << std::endl;
			return zh;
		}
		zoo_wget_children(zh, Path, watcher, 0, &svector);
		return zh;
	}

	void registerNode(zhandle_t* zh, const char* path, const char* value){
		char path_buff[1024];
		zoo_create(zh, path, value, strlen(value), &ZOO_OPEN_ACL_UNSAFE, 0, path_buff, 1024);
		std::cout << "registerNode " << path_buff << std::endl;
	}
};

#endif

/*
using namespace SNODE;

int main(int argc, char** argv){
	zhandle_t* zh = initZkp(argv[1]);
	//registerNode(zh, "/Server/Hall/21001", "127.0.0.1:9881");
	int n =0;
	while(n<1000){
		sleep(5);
		n++;
	}
	return 0;
}


	for (int i=0; i<vec.count; i++){
		std::cout << vec.data[i] << std::endl;
	}
*/