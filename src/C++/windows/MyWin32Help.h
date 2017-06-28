#ifndef __MyWin32Help_H__
#define __MyWin32Help_H__
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <mmstream.h>
#pragma comment(lib, "WINMM.LIB")

class MyWin32Help
{
public:
	//判断该id的进程是否存在
	static bool IsExistFromProcessId(DWORD id)
	{
		PROCESSENTRY32 pe;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapshot, &pe))
			return 0;
		while (true)
		{
			pe.dwSize = sizeof(PROCESSENTRY32);
			if (Process32Next(hSnapshot, &pe) == false)
				break;
			if (id == pe.th32ProcessID)
				return true;
		}
		CloseHandle(hSnapshot);
		return false;
	}

	// 高精度休眠
	static int HiResSleep(int msecs)
	{
		HANDLE hTempEvent = CreateEvent(0, true, FALSE, L"TEMP_EVENT");
		timeSetEvent(msecs, 1, (LPTIMECALLBACK)hTempEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
		WaitForSingleObject(hTempEvent, msecs);
		CloseHandle(hTempEvent);
		return 0;
	}

	// 获得当前时间
	static std::string GetCurTime()
	{
		SYSTEMTIME sys;
		char buf[64] = { 0 };

		GetLocalTime(&sys);
		sprintf(buf,"%4d/%02d/%02d %02d:%02d:%02d.%03d", 
			sys.wYear, 
			sys.wMonth, 
			sys.wDay, 
			sys.wHour, 
			sys.wMinute, 
			sys.wSecond, 
			sys.wMilliseconds);
		return std::string(buf);
	}

	// 高精度计时
	static LARGE_INTEGER GetCurClockCount()
	{
		LARGE_INTEGER m_nFreq;
		LARGE_INTEGER m_nBeginTime;
		QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期  
		QueryPerformanceCounter(&m_nBeginTime);// 获取时钟计数 
		return m_nBeginTime;
	}
	static double GetInervalTime(LARGE_INTEGER begin, LARGE_INTEGER end)
	{
		LARGE_INTEGER m_nFreq;
		QueryPerformanceFrequency(&m_nFreq);
		return (double)(end.QuadPart - begin.QuadPart) * 1000 / m_nFreq.QuadPart;
	}


};

#endif