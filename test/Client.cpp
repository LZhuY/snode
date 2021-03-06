#include "../src/base/Buff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace SNODE;

int main(int argc, char** argv){
	if(argc < 2)
		return -1;

	struct sockaddr_in serveradd;
	memset(&serveradd, 0, sizeof(serveradd));

	serveradd.sin_port = htons(atoi(argv[1]));
	serveradd.sin_family = AF_INET;
	serveradd.sin_addr.s_addr = inet_addr(argv[2]);
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr*)&serveradd, sizeof(serveradd));

	SNODE::Buff buff;
	int fid = 1;
	int i = 1024;
	std::string msg("12345");
	buff >> fid >> i >> msg;
	buff.preappend(buff.size());

	send(fd, buff.data(), buff.size(), 0);
}