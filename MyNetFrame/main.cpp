#include <iostream>
#include "MySock.h"

using namespace std;

int main(int argc, char *argv[])
{
    MySock server(NULL,19999);
    server.Bind();
    server.Listen(10);
    cout << "Hello World!" << endl;
    return 0;
}
