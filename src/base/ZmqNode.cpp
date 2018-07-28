#include "ZmqNode.h"
#include <iostream>

namespace SNODE{

ZmqNode::ZmqNode(int itype):itype_(itype){
	ctx_ = zmq_ctx_new();
    if(ctx_ == NULL)
        std::cout << "zmq_ctx_new error" << std::endl;
	sock_ = zmq_socket(ctx_, itype);
    if(sock_ == NULL)
        std::cout << "zmq_socket error" << std::endl;
    std::cout << "zmqnode init" << std::endl;
}

ZmqNode::~ZmqNode(){
	zmq_close(sock_);
	zmq_ctx_destroy(ctx_);
}

void ZmqNode::lock(){}
void ZmqNode::unlock(){}

int ZmqNode::bind(const char* addr){
	zmq_bind(sock_, addr);
}

int ZmqNode::connect(const char* addr){
	zmq_connect(sock_, addr);
}

void ZmqNode::setOpt(int opt, const char* val, size_t sz){
    std::cout << opt << val << sz << std::endl;
	int code = zmq_setsockopt(sock_, opt, val, sz);
}

int ZmqNode::sendMsg(Zmqmsg* zMsg){
    lock();
    do{
        if(ZMQ_ROUTER == itype_)
        {
            if(zmq_send(sock_, zMsg->szDst, strlen(zMsg->szDst), ZMQ_SNDMORE) < 0)
            {
                break;
            }
            if(zmq_send(sock_, "", 0, ZMQ_SNDMORE) < 0)
            {
                break;
            }
            if(zmq_send(sock_, zMsg->szSrc, strlen(zMsg->szSrc), ZMQ_SNDMORE) < 0)
            {
                break;
            }
        }
        else if (ZMQ_DEALER == itype_)
        {
            if(zmq_send(sock_, "", 0, ZMQ_SNDMORE) < 0)
            {
                break;
            }
            if(zmq_send(sock_, zMsg->szDst, strlen(zMsg->szDst), ZMQ_SNDMORE) < 0)
            {
                break;
            }
        }

        if(zmq_send(sock_, "", 0, ZMQ_SNDMORE) < 0)
        {
            break;
        }
        if(zmq_send(sock_, zMsg->szMsg, strlen(zMsg->szMsg), 0) < 0)
        {
            break;
        }
    }while(0);
    errno = 0;
    zmq_strerror(errno);
    unlock();
    return errno;
}

int ZmqNode::recvMsg(Zmqmsg* zMsg){
    lock();
    do{
        if(ZMQ_ROUTER == itype_)
        {
            if(zmq_recv(sock_, zMsg->szSrc, sizeof(zMsg->szSrc), 0) < 0)
            {
                break;
            }
            if(zmq_recv(sock_, NULL, 0, 0) < 0)
            {
                break;
            }
        }
        else if (ZMQ_DEALER == itype_)
        {
            if(zmq_recv(sock_, NULL, 0, 0) < 0)
            {
                break;
            }
        }

        if(zmq_recv(sock_, zMsg->szDst, sizeof(zMsg->szDst), 0) < 0)
        {
            break;
        }
        if(zmq_recv(sock_, NULL, 0, 0) < 0)
        {
            break;
        }
        if(zmq_recv(sock_, zMsg->szMsg, sizeof(zMsg->szMsg), 0) < 0)
        {
            break;
        }
    }while(0);
    unlock();
   	errno = 0;
    zmq_strerror(errno);
    return errno;
}

}