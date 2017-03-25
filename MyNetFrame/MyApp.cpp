#include "MyApp.h"
#include "MyTask.h"
#include <sys/epoll.h>

using namespace my_master;
MyApp::MyApp(int thread_size, int ev_size)
{
    m_evSize = ev_size;
    m_threadSize = thread_size;
    m_cur_thread_size = 0;
    m_cur_ev_size = 0;
    InitApp();
}
MyApp::~MyApp()
{}
int MyApp::InitApp()
{
    // epoll create
    m_epollFd = epoll_create(m_evSize);
#ifdef USE_LOG
    MyDebug("Get Epoll fd = %d", m_epollFd);
#endif
#if DEBUG_INFO
    printf("Get Epoll fd = %d\n", m_epollFd);
#endif
    // task create
    for(int i = 0; i < m_threadSize; ++i)
    {
        CreateTask();
    }
    return 0;
}
int MyApp::CreateTask()
{
    // TODO...
    MyTask* task = new MyTask;
    m_idle_tasks.AddTail(task);
    this->AddEvent(task);

    ++m_cur_thread_size;
    return 0;
}

int MyApp::AddEvent(MyEvent* ev)
{
    // TODO...
    struct epoll_event event;

    event.data.ptr = ev;
    event.events = EPOLLIN;
    int res = epoll_ctl(m_epollFd,EPOLL_CTL_ADD,ev->GetEventFd(),&event);
#ifdef USE_LOG
    if(res)
        MyDebug("add event fail %d",res);
#endif
#if DEBUG_INFO
    if(res)
        printf("add event fail %d\n",res);
#endif
    ++m_cur_ev_size;
    return res;
}

int MyApp::DelEvent(MyEvent* ev)
{
    int res = epoll_ctl(m_epollFd,EPOLL_CTL_DEL,ev->GetEventFd(),NULL);
#ifdef USE_LOG
    if(res)
        MyDebug("del event fail %d", res);
#endif
#if DEBUG_INFO
    if(res)
        printf("del event fail %d\n", res);
#endif
    --m_cur_ev_size;
    return res;
}

int MyApp::Exec()
{
    // TODO...
#if 0
    char ch;
    while((ch = getchar()) != 'q')
    {
        printf("send msg\n");
        for(int i = 0; i < m_idle_tasks.Count(); ++i)
        {
            MyTask* task = (MyTask*)m_idle_tasks.GetData(i);
            task->SendMsg((uint8_t*)&ch,1);
        }
    }
#endif
    return 0;
}
//////////////////////////////////////////////////// thread virtual method (do nothing)
void MyApp::Run()
{}
void MyApp::OnInit()
{}
void MyApp::OnExit()
{}
