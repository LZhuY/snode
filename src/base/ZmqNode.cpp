#include "ZmqNode.h"

ZmqNode::ZmqNode(int itype):itype_(itype){
	ctx_ = zmq_ctx_new();
	sock_ = zmq_socket(ctx_, itype);
}

ZmqNode::~ZmqNode(){
	zmq_close(sock_);
	zmq_ctx_destroy(ctx_);
}

void ZmqNode::lock(){}
void ZmqNode::unlock(){}

int ZmqNode::bind(std::stirng& addr){
	zmq_bind(sock_, addr.data());
}

int ZmqNode::connect(std::string& addr){
	zmq_connect(sock_, addr.data());
}

void ZmqNode::setOpt(int opt, const void* val, int sz){
	zmq_setsockopt(sock_, opt, val, sz);
}

int ZmqNode::sendMsg(Zmqmsg& zMsg){
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
    int errno = 0;
    zmq_strerror(errno);
    unlock();
    return errno;
}

int ZmqNode::recvMsg(Zmqmsg& zMsg){
    lock();
    do{
        if(ZMQ_ROUTER == itype)
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
        else if (ZMQ_DEALER == itype)
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
   	int errno = 0;
    zmq_strerror(errno);
    return errno;
}