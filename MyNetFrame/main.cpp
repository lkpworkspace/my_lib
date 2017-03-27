#include "Common.h"
#include "MyTcp.h"
#include "MyApp.h"

using namespace my_master;
//#define TEST

#ifdef TEST
class A : public MyNode
{
public:
    A(int a){
        this->a = a;
    }
    int a;
};

int main()
{
    int x = 10;
    MyDebug("okok%d\n",x);
#if 1
    MyList list;
    list.AddTail(new A(10));

    A* begin = (A*)list.Begin();
    A* end = (A*)list.End();
    printf("begin pointer %p\n",begin);
    printf("end pointer %p\n",end);
    while(begin != end)
    {
        std::cout << ((A*)begin)->a << std::endl;
        printf("begin pointer %p\n",begin);
        begin = (A*)(begin->next);
        printf("begin pointer %p\n",begin);
    }
    std::getchar();
#endif
    return 0;
}
#else
#if 1
// server
class MyServer: public MyTcpServer
{
public:
    MyServer(std::string ip,uint16_t port)
        :MyTcpServer(ip,port)
    {
        Bind();
        Listen();
        SetNonblock(true);
    }

    void* CallBackFunc(MyEvent *ev)
    {
        printf("Get client connect\n");
        MyTcpServer* serv = (MyTcpServer*)ev;
        while(1)
        {
            int fd = serv->Accpet(NULL,NULL);
            if(fd < 0)
                break;
            write(fd,"heheda",6);
        }
        printf("accept is hahaha\n");
    }
};

int main(int argc, char *argv[])
{
    MyApp app{1,1024};
    MyServer *server = new MyServer("",9999);

    app.AddEvent(server);
    //MyTcpServer *server = new MyTcpServer("",9999);
    //app.AddEvent(server);

    app.Exec();
#if 0
    MyTcp server("",19999);
    server.Bind();
    server.Listen(10);
    int fd = server.Accpet(NULL,NULL);

    char buf[20] = {0};
    int res = 0;
    while(true)
    {
        res = read(fd,buf,20);
        printf("read %d byte : %s\n",res,buf);
        memset(buf,0,20);
    }
#endif
    return 0;
}
#else
// client
int main(int argc, char *argv[])
{
    MyTcp client("127.0.0.1",19999,false);
    client.Connect();

    char buf[20] = {0};
    int res = 0;
    while(true)
    {
        fscanf(stdin,"%s",buf);
        res = client.Write(buf,20);
        //printf("read %d byte : %s\n",res,buf);
        memset(buf,0,20);
    }
    return 0;
}
#endif
#endif
