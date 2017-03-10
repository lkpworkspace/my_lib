#ifndef __MyLog_H__
#define __MyLog_H__
#include <fstream>
#include <windows.h>
class MyLog
{
public:
	MyLog(std::string logName);
	~MyLog();
	int AddLog(const char* pszLogTxt);
	void SetLogPath(const char* szLogPath);
	int ClearLog();
protected:
	char m_szLogPath[MAX_PATH];    // ÎÄ¼þÂ·¾¶ 
	FILE* m_pLogFile;
	CRITICAL_SECTION m_Log_cs;
	
};
#endif // MyLog_h__
