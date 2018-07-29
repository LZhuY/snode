#include "../base/Buff.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace SNODE;

int main(int argc, char** argv){
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "connect 111" << std::endl;
	int res = connect(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	std::cout << "connect 222" << " res=" << res << std::endl;
	Buff buff;
	int fid = 101;
	int i = 1001;
	std::string str("abcdef");
	buff >> fid >> i >> str;
	buff.addSize();
	std::cout << "send 111" << std::endl;
	send(fd, buff.data(), buff.size(), 0);
	char cache[1024];
	int n = 0;
	std::cout << "send 222" << std::endl;
	while(true){
		n=recv(fd, cache, 1024, 0);
		if(n > 0){
			cache[n] = '\0';
			std::cout << cache << " " << n << std::endl;
		}
	}
	return 0;
}