#include "MyThread.h"

MyThread::MyThread()
{
	hThr_ = INVALID_HANDLE_VALUE;
	bExit_ = true;
	InitializeCriticalSection(&gg_cs);
}

MyThread::~MyThread()
{
	DeleteCriticalSection(&gg_cs);
}

bool MyThread::StartThread()
{
	bExit_ = false;
	if (hThr_ != INVALID_HANDLE_VALUE) return false;
	UINT threadID;
	hThr_ = (HANDLE)_beginthreadex(NULL, 0, ListenThread, this, 0, &threadID);
	if (!hThr_) return false;
	return true;
}

bool MyThread::StopThread()
{
	if (hThr_ != INVALID_HANDLE_VALUE && !bExit_)
	{
		bExit_ = true;
		Sleep(100);
		CloseHandle(hThr_);
		hThr_ = INVALID_HANDLE_VALUE;
	}
	return true;
}

UINT WINAPI MyThread::ListenThread(void* param)
{
	MyThread* pThis = reinterpret_cast<MyThread*>(param);
	while (!pThis->bExit_)
	{
		pThis->RunThread();
	}
	return 0;
}