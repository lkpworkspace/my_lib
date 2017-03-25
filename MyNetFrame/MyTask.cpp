#include "MyTask.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
using namespace my_master;
MyTask::MyTask()
{
    m_status = TASK_STATUS::STOP;
    m_msgFd[0] = -1;
    m_msgFd[1] = -1;
    memset(m_msgBuf,0,MSG_LEN);
    //sem_init(&m_event,0,0);
    m_que.Clear(true);
    m_recv.Clear(true);
    CreateSockPair();
    this->Start();
}
MyTask::~MyTask(){ClearResource();}
////////////////////////////////////////////////////Runing thread
void MyTask::Run()
{
    memset(m_msgBuf,0,MSG_LEN);
    if(WaitMsg(m_msgBuf,MSG_LEN) > 0)
    {
        // TODO...
        TaskWork();
    }else
    {
        this->Stop();
        m_status = TASK_STATUS::ERROR;
    }
}
int MyTask::TaskWork()
{
    // TODO...
#if 0
    while(!m_que.IsEmpty())
    {

    }
#endif
    printf("task %d work...\n",GetThreadId());
    return 0;
}
////////////////////////////////////////////////////TODO...
int MyTask::SendMsg(const uint8_t* buf, int len)
{
    // process event
    return write(m_msgFd[1],buf,len);
}

int MyTask::WaitMsg(uint8_t* buf, int len)
{
    return read(m_msgFd[0],buf,len);
}
void MyTask::OnInit()
{
    MyThread::OnInit();
#ifdef USE_LOG
    MyDebug("thread %u begin", GetThreadId());
#endif
#if DEBUG_INFO
    printf("thread %u begin\n", GetThreadId());
#endif
}
void MyTask::OnExit()
{
    MyThread::OnExit();
#ifdef USE_LOG
    MyDebug("thread %u quit", GetThreadId());
#endif
#if DEBUG_INFO
    printf("thread %u quit\n", GetThreadId());
#endif
}
int MyTask::CreateSockPair()
{
    int res = -1;
    res = socketpair(AF_UNIX,SOCK_DGRAM,0,m_msgFd);
#ifdef USE_LOG
    MyDebug("create socketpair %d",res);
#endif
#if DEBUG_INFO
    printf("create socketpair %d\n",res);
#endif
    Common::SetNonblock(m_msgFd[0],false);
    Common::SetNonblock(m_msgFd[1],true);
    return res;
}
////////////////////////////////////////////////////assist function
void MyTask::ErrorProcess()
{
    ClearResource();
    m_status = TASK_STATUS::ERROR;
}
void MyTask::ClearResource()
{
    this->Stop();
    close(m_msgFd[0]);
    close(m_msgFd[1]);
    //sem_destroy(&m_event);
}







































