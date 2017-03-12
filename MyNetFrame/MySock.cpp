#include "MySock.h"
#include <fcntl.h>
#include <assert.h>
#include "MyEvent.h"
using namespace my_master;
MySock::MySock(std::string ip, uint16_t port, int type, bool isServer) // type: TCP/UDP
    :m_sock(-1),
      m_port(port),
      m_ip(ip),
      m_class_type(0x00)
{
    // init event class
    this->m_type = MyEvent::SOCK;

    memset(&m_addr,0,sizeof(struct sockaddr_in));
    m_sock = Socket(AF_INET,type,0);

    if(isServer)
    {
        m_class_type |= 0x01;
    }else
    {
        m_class_type |= 0x00;
    }
    switch(type)
    {
    case SOCK_STREAM:
        m_class_type |= 0x02;
        break;
    case SOCK_DGRAM:
        m_class_type |= 0x04;
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////////// server
int MySock::Listen(int backlog)
{
    int res = -1;
    //SetNonblock();
    res = listen(m_sock,backlog);
    assert(res == 0);
    return res;
}

int MySock::Accpet(struct sockaddr *addr, socklen_t *addrlen)
{
    int res = accept(m_sock,addr,addrlen);
    assert(res != -1);
    return res; // file descriptor
}
//////////////////////////////////////////////////// client
int MySock::Read(char* buf,int len)
{
    return read(m_sock,buf,len);
}

int MySock::Write(char* buf,int len)
{
    return write(m_sock,buf,len);
}
int MySock::Connect()
{
    int ret;
    //struct sockaddr_in addr;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ip.c_str(), &m_addr.sin_addr);

    ret = connect(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr));
    assert(ret == 0);
    return ret;
}
/////////////////////////////////////////////////// share
void* MySock::Callback(void *)
{
    return NULL;
}
/// setting nonblocking
int MySock::SetNonblock(bool b)
{
    return Common::SetNonblock(m_sock,b);
}
int MySock::Socket(int domin, int type, int protocol)
{
    int sock = socket(domin,type,protocol);
    assert(sock > 0);
    return sock;
}
int MySock::Bind()
{
    int res;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(m_port);
    if(!m_ip.empty())
        inet_pton(AF_INET, m_ip.c_str(), &m_addr.sin_addr);
    else
        m_addr.sin_addr.s_addr = INADDR_ANY;

    res = bind(m_sock, (struct sockaddr*)&m_addr, sizeof(m_addr));
    assert(res == 0);
    return res;
}
int MySock::Close()
{
    int res = close(m_sock);
    assert(res == 0);
    return res;
}
