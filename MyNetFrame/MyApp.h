#ifndef MYAPP_H
#define MYAPP_H
#include "Common.h"
namespace my_master {

class MyApp : public MyThread
{
public:
    MyApp(int thread_size = 2,int ev_size = 1024);
    ~MyApp();

    int AddEvent(MyEvent* ev);
    int DelEvent(MyEvent* ev);
    int Exec();                        // mainloop
private:
    int InitApp();
    void Run();                        // override Mythread method (do nothing)
    void OnInit();                     // override Mythread method (do nothing)
    void OnExit();                     // override Mythread method (do nothing)
    int CreateTask();                  // create thread
private:
    my_master::MyList m_work_tasks;    // save MyTask class
    my_master::MyList m_idle_tasks;    // save MyTask class
    my_master::MyList m_ev_recv;       // recv task event, save MyEvent class
    int m_epollFd;                     // listen Event file des
    int m_evSize;                      // can be listened (const var)
    int m_threadSize;                  // thread size (const var)
    int m_cur_thread_size;             // how many task was create
    int m_cur_ev_size;                 // how many ev was create
};

}
#endif // MYAPP_H
