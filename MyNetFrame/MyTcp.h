#ifndef MYTCP_H
#define MYTCP_H
#include "Common.h"
#include "MySock.h"

namespace my_master {

class MyTcp : public my_master::MySock
{
public:
    MyTcp(std::string ip,uint16_t port, bool isServer = true);
    ~MyTcp();
    //////////////////////////////////// override MySock method, client used
    int Read(char* buf, int len);
    int Write(char*buf,int len);

    int Listen(int backlog = 10);// ok
    int Connect(); // ok
    int Accpet(struct sockaddr *addr, socklen_t *addrlen); // ok
};

} // end namespace
#endif // MYTCP_H
