#ifndef __MYNET_H__
#define __MYNET_H__
#include "Common.h"
#ifdef WIN32
#else
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#endif

class MyNet
{
public:
    MyNet();
    ~MyNet();
};

#endif // MYNET_H
