#ifndef __MyWin32Help_H__
#define __MyWin32Help_H__
#include <Windows.h>
#include <TlHelp32.h>

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

};

#endif