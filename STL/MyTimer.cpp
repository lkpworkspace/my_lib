#include "MyTimer.h"

bool MyTimer::isStart_ = false;
bool MyTimer::isExit_ = true;
std::thread* MyTimer::timer_ = nullptr;
std::mutex MyTimer::mutex_;
std::multimap<clock_t, Timer_t*> MyTimer::timers_;



void MyTimer::Start()
{
	if (isStart_) return;
	isStart_ = true;
	isExit_ = false;
	timer_ = new std::thread(MyTimer::Run);
	timer_->detach();
}

void MyTimer::Stop()
{
	isStart_ = false;
	isExit_ = true;
#ifdef WIN32
	Sleep(500);
#else
	usleep(500*1000);
#endif
	delete timer_;
	timer_ = nullptr;
}

void MyTimer::Run()
{
	std::vector<timer_iter> temp_iter;
	std::vector<timer_iter>::iterator temp_begin;
	std::vector<timer_iter>::iterator temp_end;
	while (true)
	{
		if (isExit_) break;
		Timer_t* timer;
		double temp = 0;
		std::pair<timer_iter, timer_iter> range;

		mutex_.lock();
		if (timers_.empty()){
			mutex_.unlock();
			continue;
		} 
		// 响应最近的定时器
		range = timers_.equal_range(timers_.begin()->first);
		for (timer_iter iter = range.first; iter != range.second; ++iter)
		{
			timer = iter->second;
			if (timer != NULL && timer->timeout < clock())
			{
				//std::cout << timer->timeout << "  " << clock() << std::endl;
				timer->callback(timer->arg);
				temp_iter.push_back(iter);
				temp = (timer->interval / 1000.0) * CLOCKS_PER_SEC;
				timer->timeout = clock() + (int)temp;
				timers_.insert(std::pair<clock_t, Timer_t*>(
					timer->timeout + (int)temp, timer));
			}
		}
		// 删除过期的定时器
		for (temp_begin = temp_iter.begin(),temp_end = temp_iter.end(); 
			temp_begin != temp_end; 
			++temp_begin)
		{
			timers_.erase(*temp_begin);
		}
		temp_iter.clear();
		mutex_.unlock();
	}
}

// interval : 单位毫秒
// callback : 回掉函数
bool MyTimer::AddTimer(int interval, void (*callback)(void*), void* arg)
{
	if (!isStart_) return false;
	double temp = (interval / 1000.0) * CLOCKS_PER_SEC;
	Timer_t* timer = new Timer_t;

	timer->callback = callback;
	timer->interval = interval;
	timer->timeout = clock() + (int)temp;
	timer->arg = arg;

	mutex_.lock();
	timers_.insert(std::pair<clock_t, Timer_t*>(timer->timeout + (int)temp, timer));
	mutex_.unlock();
	return true;
}