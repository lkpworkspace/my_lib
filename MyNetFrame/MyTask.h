#ifndef __MYTASK_H__
#define __MYTASK_H__
#include "Common.h"
#include "MyThread.h"
#include "MyEvent.h"
#include <semaphore.h>

namespace my_master {
#define MSG_LEN 1
class MyTask : public MyThread
{
    friend class MyApp;
public:
    enum TASK_STATUS{
        RUNING,
        IDLE,
        STOP,
        ERROR
    };
public:
    MyTask();
    ~MyTask();
    void Run();    // override
    void OnInit(); // override
    void OnExit(); // override

    int SendMsg(const uint8_t* buf, int len);   // invoke by MyApp
    int WaitMsg(uint8_t *buf, int len);         // invoke by myself
    int ProcessMsg();                           // process MyApp event
private:
    int CreateSockPair();   // communication between thread
    void ClearResource();
    void ErrorProcess();
private:
    TASK_STATUS m_status;                // current thread runing status
    int m_msgFd[2];                      // 0 used by myself, 1 used by MyApp
    my_master::MyList<MyEvent*> m_que;   // task queue
    uint8_t m_msgBuf[MSG_LEN];
    sem_t m_event;
};

} // end namespace
#endif // MYTASK_H
