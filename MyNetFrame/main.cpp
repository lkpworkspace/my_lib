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
#if 0
    MyList list;
    list.AddTail(new A(10));
    list.AddTail(new A(11));

    MyList list1;
    list1.AddTail(new A(90));
    list1.AddTail(new A(2));

    list.Append(&list1);

    MyNode* begin = list.GetData(0);

    for(int i = 0; i < list.Count(); ++i)
    {
        std::cout << ((A*)begin)->a << std::endl;
        begin = begin->next;
    }
#endif
    return 0;
}
#else
#if 1
// server
int main(int argc, char *argv[])
{
    MyApp app;

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
