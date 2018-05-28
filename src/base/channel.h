#ifndef CHANNEL_H
#define CHANNEL_H

extern const int MAX_LINE = 1024;
extern const int 
namespace SNODE{
class Channel{
public:
	Channel(int fd);
	~Channel();

	void setReadFunc(std::function&& func);
	//void setWriteFunc(std::function&& func);
	void setConnFunc(std::function&& func);

	void onRead();
	void onConn(int fd);
	void onWrite();

	bool write(const char* buff, int sz);
	bool isListen(){ return islisten_; };
	void evenHandler();
private:
	int fd_;
	std::function<void (const char*, int sz)> readhandler_;
	//std::function<void (Channel&)> writehandler_;
	std::function<void (int fd)> connhandler_;
	char inbuff_[MAX_LINE];
	char outbuff_[MAX_LINE];

	int loutpos_;
	int routpos_;

	int linpos_;
	int rinpos_;

	int revents_;
	bool islisten_;
	//std::function<void (const Message*)> readhandler_;
};
}
#endif