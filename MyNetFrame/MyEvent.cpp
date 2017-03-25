#include "MyEvent.h"
using namespace my_master;
MyEvent::MyEvent()
    :m_callback(nullptr)
{}

MyEvent::~MyEvent()
{}

void MyEvent::SetCallBack(callback_t cb)
{ m_callback = cb; }
