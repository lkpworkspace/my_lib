#ifndef MYSOCK_H
#define MYSOCK_H
#include "MyNet.h"
#include "Common.h"

/*
* type: low ----> height
*    1bit: 0 server; 1 client;
*    2bit: 1 tcp
*    3bit: 1 udp
*/
#define IS_SERVER(type) (type & 0x01)
#define IS_TCP(type) (type & 0x02)
#define IS_UDP(type) (type & 0x04)

class MySock // TCP or UDP; server or client
{
    friend class MyEvent;
public:
    MySock(std::string ip,uint16_t port,int type = SOCK_STREAM, bool isServer = true);
    ~MySock(){Close();}

public:
    int Read(char* buf,int len);
    int Write(char*buf,int len);
    int Bind(); // ok
    int Listen(int backlog = 10);// ok
    int Connect(); // ok
    int Accpet(struct sockaddr *addr, socklen_t *addrlen); // ok
    int Close(); // ok
    int SetNonblock(bool b = true); // ok
private:
    int Socket(int domin, int type, int protocol);//ok
private:
    uint8_t m_class_type;          // tcp/udp or server/client.
    std::string m_ip;              // if server, bind ip; if client, connect ip.
    int m_sock;                    // socket file descritor.
    uint16_t m_port;               // if server, bind port; if client, connect port.
    struct sockaddr_in m_addr;     // if server, save self addr; if client, save client addr.
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
