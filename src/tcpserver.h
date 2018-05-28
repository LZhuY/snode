#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>

namespace SNODE{

class TcpServer: public Server{
	void listen(std::string& ip, int port);
	void start();
	void stop();
};

}
#endif