#ifndef __MyThread_H__
#define __MyThread_H__
#include <thread>
#include <mutex>

class MyThread
{
public:
	MyThread();
	~MyThread();
	virtual void Run() = 0;
	void Start();
	void Stop();
protected:
	static void ListenThread(void*);
	std::mutex mutex_;
private:
	std::thread* thread_;
	bool isRuning_;
};

#endif