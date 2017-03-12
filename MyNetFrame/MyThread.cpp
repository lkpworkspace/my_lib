#include "MyThread.h"
using namespace my_master;
MyThread::MyThread()
{
    m_thread = nullptr;
    m_isRuning = false;
}

MyThread::~MyThread()
{ Stop(); }

void MyThread::Start()
{
    if (!m_thread)
	{
        m_isRuning = true;
        m_thread = new std::thread(&MyThread::ListenThread,this);
        m_id = m_thread->get_id();
        m_thread->detach();
	}	
}

void MyThread::Stop()
{
    m_isRuning = false;
    if (m_thread)
        delete m_thread;
    m_thread = nullptr;
}

void MyThread::ListenThread(void* obj)
{
	MyThread* t = (MyThread*)obj;
    t->OnInit();
    while (t->m_isRuning)
	{
		t->Run();
	}
	t->OnExit();
}
