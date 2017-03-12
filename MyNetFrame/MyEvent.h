#ifndef MYEVENT_H
#define MYEVENT_H
#include "Common.h"

namespace my_master {


class MyEvent
{
    friend class MyTask;
    friend class MyApp;
public:
    enum EVENT_TYPE{
        SOCK,
        NONE
    };
public:
    MyEvent();
    MyEvent(EVENT_TYPE type);
    virtual void* Callback(void*) = 0;
public:
    EVENT_TYPE m_type;
    int m_eventFd;
private:      
    //my_master::MyList<> m;
};

} // end namespace
#endif // MYEVENT_H
