#ifndef __MyTimer_H__
#define __MyTimer_H__
#include <set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <time.h>
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct Timer_t
{
	int interval;
	clock_t timeout;
	//bool isStop;
	void (*callback)(void*);
	void* arg;
}Timer_t;
class MyTimer
{
public:
	static void Start();
	static void Stop();
	static bool AddTimer(int interval, void (*callback)(void*), void* arg);
private:
	MyTimer(){}
	static void Run();
private:
	typedef std::multimap<clock_t, Timer_t*>::iterator timer_iter;
	static bool isStart_;
	static bool isExit_;
	static std::multimap<clock_t,Timer_t*> timers_;
	static std::thread* timer_;
	static std::mutex mutex_;
};

// DEMO
//#include "MyTimer.h"
//
//void callback(void* arg)
//{
//	std::cout << "run" << std::endl;
//}
//
//void callback2(void* arg)
//{
//	std::cout << "run2" << std::endl;
//}
//
//int main()
//{
//	MyTimer::Start();
//	MyTimer::AddTimer(2000, callback, NULL);
//	MyTimer::AddTimer(500, callback2, NULL);
//	while (true)
//	{
//		Sleep(500);
//		std::cout << "main thread" << std::endl;
//	}
//
//	std::cin.get();
//	return 0;
//}
#endif