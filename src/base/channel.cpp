#include "channel.h"

namespace SNODE{

Channel::Channel(int fd):fd_(fd){

}

void Channel::setReadFunc(ReadFunc&& func){
	readhandler_ = std::move(func);
}
/*void Channel::setWriteFunc(std::function&& func){
	writehandler_ = std::move(func);
}*/
void Channel::setConnFunc(ConnectFunc&& func){
	connhandler_ = std::move(func);
}

void Channel::onRead(){
	int sz = read(fd_, inbuff_+rinpos_, MAX_LINE);
	rinpos_ += sz;
	readhandler_(inbuff_+linpos_, sz);
	linpos_ += sz;
/*	context_->parse();
	if(context_->isComplate()){
		Message* msg = context_->getMessage();

	}*/
}

void Channel::onWrite(){
	int sz = write(fd_, outbuff_+loutpos_, routpos_-loutpos_);
	loutpos_ += sz;

	if(routpos_ > loutpos_){
		memmove(outbuff_, outbuff_+loutpos_, routpos_-loutpos_);
	}
	routpos_ -= loutpos_;
	loutpos_ = 0;
}

bool Channel::write(const char* buff, int sz){
	if(routpos_ + sz > MAX_LINE)
		return false;
	memcpy(outbuff_+routpos_, buff, sz);
	routpos_ += sz;
	return true;
}
void Channel::onConn(int fd){
	connhandler_(fd);
}

void Channel::evenHandler(){
	switch(revents_){
		case EPOLLIN :
			if(isListen())
				onConn(fd);
			else
				onRead();
		case EPOLLOUT:
			onWrite();
		default:
			//
	}
}

void Channel::listen(std::string ip, int port){
	struct sockaddr_in serveraddr;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	SetSocketBlockingEnabled(fd);
	memset(&serveraddr, 0, sizeof(sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htol(INADDR_ANY);
	serveraddr.sin_port = htons(port);
	bind(fd, (struct sockaddr*)&serveraddr, sizeof(sockaddr_in));
	listen(fd, 10);
	fd_ = fd;
}

/*void Channel::setContext(std::shared_ptr<Context> context){
	context_ = context;
}*/

}