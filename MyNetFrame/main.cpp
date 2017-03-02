#include <iostream>
#include "MySock.h"
#include <stdio.h>

using namespace std;

#if 0
// server
int main(int argc, char *argv[])
{
    MySock server("",19999);
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
    return 0;
}
#else
// client
int main(int argc, char *argv[])
{
    MySock client("127.0.0.1",19999,SOCK_STREAM,false);
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
