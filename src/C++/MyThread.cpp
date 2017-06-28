#include "MyThread.h"

MyThread::MyThread()
{
	thread_ = nullptr;
	isRuning_ = false;
}

MyThread::~MyThread()
{}

void MyThread::Start()
{
	if (!thread_)
	{
		isRuning_ = true;
		thread_ = new std::thread(&MyThread::ListenThread,this);
		thread_->detach();
	}	
}

void MyThread::Stop()
{
	isRuning_ = false;
	if (thread_)
		delete thread_;
	thread_ = nullptr;
}

void MyThread::ListenThread(void* obj)
{
	MyThread* t = (MyThread*)obj;
	t->OnInit();
	while (t->isRuning_)
	{
		t->Run();
	}
	t->OnExit();
}
