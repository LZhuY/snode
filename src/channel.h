#ifndef CHANNEL_H
#define CHANNEL_H

class Channel{
public:
	Channel(int fd);
	~Channel();

	void setReadFunc(std::function&& func);
	void setWriteFunc(std::function&& func);
	void setConnFunc(std::function&& func);

	void onRead(int fd);
	void onWrite(int fd);
	void onConn(int fd);
private:
	int fd_;
	std::function<void (const char*)> readhandler_;
	std::function<void (Channel&)> writehandler_;
	std::function<void (int fd)> connhandler_;
	//std::function<void (const Message*)> readhandler_;
};

#endif