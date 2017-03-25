#include "MyTcp.h"
using namespace my_master;
MyTcp::MyTcp(std::string ip, uint16_t port, bool isServer)
    :MySock(ip,port,SOCK_STREAM,isServer)
{}
MyTcp::~MyTcp()
{}
//////////////////////////////////////////////////// client
int MyTcp::Read(char* buf,int len)
{
    if(IS_SERVER(this->m_tcp_ip_type))
        return 0;
    return read(m_sock,buf,len);
}

int MyTcp::Write(char* buf, int len)
{
    if(IS_SERVER(this->m_tcp_ip_type))
        return 0;
    return write(m_sock,buf,len);
}
int MyTcp::Connect()
{
    if(IS_SERVER(this->m_tcp_ip_type))
        return -1;

    int ret;
    //struct sockaddr_in addr;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ip.c_str(), &m_addr.sin_addr);

    ret = connect(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr));
    assert(ret == 0);
    return ret;
}
//////////////////////////////////////////////////// server
int MyTcp::Listen(int backlog)
{
    if(!IS_SERVER(this->m_tcp_ip_type))
        return 0;
    int res = -1;
    //SetNonblock();
    res = listen(m_sock,backlog);
    assert(res == 0);
    return res;
}

int MyTcp::Accpet(struct sockaddr *addr, socklen_t *addrlen)
{
    if(!IS_SERVER(this->m_tcp_ip_type))
        return 0;
    int res = accept(m_sock,addr,addrlen);
    assert(res != -1);
    return res; // file descriptor
}
