#include "MyLog.h"
#include <time.h>
MyLog::MyLog(std::string logName)
{
	//char szConfigPath[MAX_PATH] = { 0 };
	//char szExePath[MAX_PATH] = { 's','t','e','p','v','r' };

	//here comment it.because unity unknow where to create this file.
	//GetModuleFileNameA(NULL, (LPCH)szExePath, MAX_PATH);
	//char *tmp = szExePath;
	//while (strchr(tmp, '\\') != NULL) 
	//{
	//	tmp = strchr(tmp, '\\') + 1;
	//}
	//szExePath[strlen(szExePath) - 4] = '\0';

	sprintf(m_szLogPath, "%s", logName.c_str());
	m_pLogFile = NULL;

	InitializeCriticalSection(&m_Log_cs);
}

MyLog::~MyLog()
{
}

int MyLog::AddLog(const char* pszLogTxt)
{
	time_t t = time(0);
	char szTime[MAX_PATH];
	strftime(szTime, sizeof(szTime), "%Y/%m/%d %X", localtime(&t));

	EnterCriticalSection(&m_Log_cs);
	m_pLogFile = fopen(m_szLogPath, "a+");
	fprintf(m_pLogFile, "[%s]:%s\n", szTime, pszLogTxt);
	fclose(m_pLogFile);
	LeaveCriticalSection(&m_Log_cs);

	return 0;
}

void MyLog::SetLogPath(const char* szLogPath)
{
	strcpy(m_szLogPath, szLogPath);
}

int MyLog::ClearLog()
{
	EnterCriticalSection(&m_Log_cs);
	m_pLogFile = fopen(m_szLogPath, "w");
	fclose(m_pLogFile);
	LeaveCriticalSection(&m_Log_cs);

	return 0;
}