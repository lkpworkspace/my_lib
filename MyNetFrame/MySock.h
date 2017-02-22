#ifndef MYSOCK_H
#define MYSOCK_H
#include "MyNet.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include<string>

class MySock // TCP or UDP; server or client
{
public:
    MySock(std::string ip,uint16_t port,int type = SOCK_STREAM);
    ~MySock();

public:
    int Read();
    int Write();

    int Socket(int domin, int type, int protocol);//ok
    int Bind(); // ok
    int Listen(int backlog = 10);// ok
    int Connect(); // ok
    int Accpet(); // ok
    int Close(); // ok
    int SetNonblock(); // ok
private:
    std::string ip_;
    int sock_;
    uint16_t port_;
};
// client:
//      connect();
//      read or write
//      close();
// server:
//      bind();
//      listen();
//      accept();
//      read or write
//      close();



// socket api
//int Socket(int domin = AF_INET, int type = SOCK_STREAM, int protocol = 0);
//int Bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
//int Listen(int sockfd, int backlog);
//int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//int Connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

#endif // MYSOCK_H
