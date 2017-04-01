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
	//�жϸ�id�Ľ����Ƿ����
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

	// �߾�������
	static int HiResSleep(int msecs)
	{
		HANDLE hTempEvent = CreateEvent(0, true, FALSE, L"TEMP_EVENT");
		timeSetEvent(msecs, 1, (LPTIMECALLBACK)hTempEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
		WaitForSingleObject(hTempEvent, msecs);
		CloseHandle(hTempEvent);
		return 0;
	}

	// ��õ�ǰʱ��
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

};

#endif