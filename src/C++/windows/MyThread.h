#ifndef __MyThread_H__
#define __MyThread_H__

#include <process.h>
#include <stdint.h>
#include <Windows.h>

class MyThread
{
public:
	MyThread();
	~MyThread();

	virtual void RunThread() = 0;
	bool StartThread();
	bool StopThread();
	CRITICAL_SECTION gg_cs;

protected:
	static UINT WINAPI ListenThread(void* param);

private:
	bool bExit_;
	HANDLE hThr_;
};


#endif