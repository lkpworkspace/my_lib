#ifndef MYAPP_H
#define MYAPP_H
#include "Common.h"
namespace my_master {

class MyTask;
class MyEvent;
class MyApp : public MyThread
{
public:
    MyApp(int ev_size, int thread_size);
    ~MyApp();

    int Init();
    int AddEvent(MyEvent*);
    int DelEvent(MyEvent*);
    int Exec();
private:
    void Run();        // override (do nothing)
    void OnInit();
    void OnExit();
    int CreateTask();
private:
    my_master::MyList<MyTask*> work_threads_;
    my_master::MyList<MyTask*> idle_threads_;
    my_master::MyList<MyEvent*> msg_queue_;
    int m_epollFd;
    int m_evSize;
    int m_threadSize;
};

}
#endif // MYAPP_H
