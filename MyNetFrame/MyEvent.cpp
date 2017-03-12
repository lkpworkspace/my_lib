#include "MyEvent.h"
using namespace my_master;
MyEvent::MyEvent()
{
    this->m_type = EVENT_TYPE::NONE;
}

MyEvent::MyEvent(EVENT_TYPE type)
{
    this->m_type = type;
}
