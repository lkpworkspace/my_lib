#include "MySock.h"
#include <fcntl.h>

MySock::MySock(std::string ip,uint16_t port,int type = SOCK_STREAM)
    :sock_(-1),
      port_(port),
      ip_(ip)
{
    sock_ = Socket(AF_INET,type,0);
}

// setting nonblocking
inline int SetNonblock()
{
    int flags = fcntl(sock_, F_GETFL, 0);
    flags |= O_NONBLOCK;
    return fcntl(sock_, F_SETFL, flags);
}

inline int MySock::Socket(int domin, int type, int protocol)
{
    int sock = socket(domin,type,protocol);
    assert(sock == 0);
    return sock;
}

inline int MySock::Bind()
{// port fd
    int res;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    if(!ip_.empty())
        inet_pton(AF_INET, ip_.c_str(), &addr.sin_addr);
    else
        addr.sin_addr.s_addr = INADDR_ANY;

    int res = bind(sock_, (struct sockaddr*)&addr, sizeof(addr));
    assert(res == 0);
    return res;
}

int MySock::Listen(int backlog)
{
    int res = -1;
    SetNonblock();
    res = listen(sock_,backlog);
    assert(res == 0);
    return res;
}

inline int MySock::Accpet(struct sockaddr *addr, socklen_t *addrlen)
{
    int res = accept(sock_,addr,addrlen);
    assert(res != -1);
    return res;
}

inline int MySock::Connect()
{
    int ret;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    inet_pton(AF_INET, ip_.c_str(), &addr.sin_addr);

    ret = connect(sock_, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0 && errno != EINPROGRESS)
    {
        Close();
        return ret;
    }
    return ret;
}

inline int MySock::Close()
{
    int res = close(sock_);
    assert(res != -1);
    return res;
}
