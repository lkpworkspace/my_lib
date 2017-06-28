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
	virtual void OnInit(){}
	virtual void OnExit(){}
	void Start();
	void Stop();
public:
	std::mutex mutex_;
protected:
	static void ListenThread(void*);
private:
	std::thread* thread_;
	bool isRuning_;
};

#endif
