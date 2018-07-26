#include "Client.h"
EchoClient::EchoClient(std::string ip, int port){
	struct sockaddr_in    servaddr;
	fd_ = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INT;
	servaddr.sin_port = htons(9981);

	memset(&servaddr, 0, sizeof(servaddr));
	inet_pton(AF_INET, ip.data(), &servaddr.sin_addr);

	int res = connect(fd_, (struct sockaddr*)&servaddr, sizeof(servaddr));
}

void EchoClient::SendMsg(Buff* buff){
	send(fd_, buff.data(), buff.size(), 0);
}

void EchoClient::Close(){
	close(fd_);
}