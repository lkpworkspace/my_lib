#ifndef MYAPP_H
#define MYAPP_H
#include "Common.h"

class MyThread;
class MyEvent;

class MyApp
{
public:
    MyApp();
    ~MyApp();

    int Init();
    int Run();

private:
    std::queue<MyThread*> work_threads_;
    std::queue<MyThread*> idle_threads_;
    std::queue<MyEvent*> msg_queue_;
};

#endif // MYAPP_H
