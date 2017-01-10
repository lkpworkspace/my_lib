#ifndef __MyEvent_H__
#define __MyEvent_H__
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <thread>
#include <mutex>
#include <queue>
#include "MyObj.h"
#include <iostream>

class MyEvent
{
public:
	~MyEvent();

	static void Start();
	static void Stop();
	static void AddEvent(MyObj*);
private:
	MyEvent();
	static void MainLoop();
private:
	static std::queue<MyObj*> task_queue_;
	static std::thread* thread_;
	static bool isExit_;
	static std::mutex mutex_;
};

#endif