#ifndef MYTCP_H
#define MYTCP_H
#include "Common.h"
#include "MySock.h"

namespace my_master {
class MyTcpSocket;
class MyTcpServer : public my_master::MySock
{
public:
    MyTcpServer(std::string ip,uint16_t port);
    ~MyTcpServer();

    //static void* CallFunc(void*);
    /////////////////////////////////
    /// virtual method
    virtual void* CallBackFunc(MyEvent *){return NULL;}

    //MyTcpSocket GetConnect();
    int Listen(int backlog = 10);
    int Accpet(struct sockaddr_in *addr, socklen_t *addrlen);
};

class MyTcpClient : public my_master::MySock
{
public:
    MyTcpClient(std::string ip,uint16_t port);
    ~MyTcpClient();
protected:
    /////////////////////////////////
    /// virtual method
    virtual void* CallBackFunc(MyEvent *){return NULL;}
public:
    int Read(char* buf, int len);
    int Write(const char *buf, int len);
    int Connect();
};

class MyTcpSocket : public my_master::MyEvent
{
public:
    MyTcpSocket(int fd, sockaddr_in addr);
    MyTcpSocket(const MyTcpSocket& other);
    ~MyTcpSocket();
    ////////////////////////////////////
    /// override MyEvent method
    int GetEventFd(){ return m_sock; }
    EVENT_TYPE GetEventType(){ return EVENT_TYPE::SOCK; }
    uint32_t GetEpollEventType(){ return EPOLLIN; }
    ////////////////////////////////////
    /// virtual method
    virtual void* CallBackFunc(MyEvent *){return NULL;}

    MyTcpSocket& operator=(MyTcpSocket& other);
    int Read(char*, int);
    int Write(const char*,int);
private:
    int m_sock;
    sockaddr_in m_addr;
};

} // end namespace
#endif // MYTCP_H
