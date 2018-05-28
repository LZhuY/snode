#include "channel.h"

Channel::Channel(int fd):fd_(fd){

}

void Channel::setReadFunc(std::function&& func){
	readhandler_ = std::move(func);
}
void Channel::setWriteFunc(std::function&& func){
	writehandler_ = std::move(func);
}
void Channel::setConnFunc(std::function&& func){
	connhandler_ = std::move(func);
}

void Channel::onRead(int fd){

}
void Channel::onWrite(int fd){

}
void Channel::onConn(int fd){
	
}