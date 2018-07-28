//comm.h
#ifndef _COMMON_H_
#define _COMMON_H_

#define NAME_LEN    256
#define MSG_LEN     1024

typedef struct {
	char szSrc[NAME_LEN];
	char szDst[NAME_LEN];
	char szMsg[MSG_LEN];
}Zmqmsg;

typedef struct {
	
}Netmsg;

typedef struct {
    void * sock;
    int iType;
}ZmqSock;

#endif