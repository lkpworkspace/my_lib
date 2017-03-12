#include "MyApp.h"
#include <sys/epoll.h>
using namespace my_master;
MyApp::MyApp(int ev_size, int thread_size)
{
    m_evSize = ev_size;
    m_threadSize = thread_size;
}
MyApp::~MyApp()
{

}
int MyApp::Init()
{
    // epoll create
    m_epollFd = epoll_create(m_evSize);
    // task create
    // TODO...
    for(int i = 0; i < m_threadSize; ++i)
    {
        CreateTask();
    }
}

int MyApp::AddEvent(MyEvent*)
{

}

int MyApp::DelEvent(MyEvent*)
{

}

int MyApp::Exec()
{

}

void MyApp::Run()
{

}
void MyApp::OnInit()
{

}
void MyApp::OnExit()
{

}
