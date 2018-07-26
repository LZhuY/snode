#include "../scr/base/Buff.h"
#include <iostream>

int main(int argc, char** argv){
	if(argc < 2)
		return -1;

	struct sockaddr_in serveradd;
	memset(&serveradd, 0, sizeof(serveradd));

	serveradd.sin_port = htons(atoi(argv[0]));
	serveradd.sin_family = AF_INET;
	serveradd.sin_addr = inet_addr(argv[1]);
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr*)&serveradd, sizeof(serveradd));

	Buff buff;
	std::string msg("12345");
	buff.append(msg.data(), msg.size());
	send(fd, buff.data(), buff.size(), 0);
}