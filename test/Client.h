#ifndef ECHO_CLIENT_H
#define ECHO_CLIENT_H

#include "../src/base/Buff.h"
#include <string>

class EchoClient{
	public:
		EchoClient(std::string ip, int port);
		void SendMsg(Buff* buff);
		void Close();
	private:
		int fd_;
};

#endif