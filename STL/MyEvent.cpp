#include "MyEvent.h"

std::queue<MyObj*> MyEvent::task_queue_;
std::thread* MyEvent::thread_ = nullptr;
bool MyEvent::isExit_ = true;
std::mutex MyEvent::mutex_;

void MyEvent::Start()
{
	if (isExit_)
	{
		isExit_ = false;
		thread_ = new std::thread(&MyEvent::MainLoop);
		thread_->detach();
	}
}

void MyEvent::Stop()
{
	if (!isExit_)
	{
		isExit_ = true;
#ifdef WIN32
		Sleep(5);
#else
#endif
		delete thread_;
		thread_ = nullptr;
	}
}

void MyEvent::AddEvent(MyObj* obj)
{
	mutex_.lock();
	task_queue_.push(obj);
	mutex_.unlock();
}

void MyEvent::MainLoop()
{
	while (!isExit_)
	{
		mutex_.lock();
		if (!task_queue_.empty())
		{
			MyObj* obj = task_queue_.front();
			obj->Run();
			//std::cout << task_queue_.size();
			task_queue_.pop();
			task_queue_.push(obj);
		}
		mutex_.unlock();
	}
}