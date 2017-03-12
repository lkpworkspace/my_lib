#ifndef __MyLog_H__
#define __MyLog_H__
#include "Common.h"
#include <mutex>

namespace my_master {

#define LOG_NAME "mylog.log"
#define MAX_PATH 255

class MyLog
{
public:
    static MyLog* GetInstance();
    static void SetLogPath(const char* path); // do not suggest to use
    int AddLog(std::string pszLogTxt);
	int ClearLog();
protected:
    static char m_szLogPath[MAX_PATH];    // file path
    FILE* m_pLogFile;                     // file pointer
    std::mutex m_log_mutex;               // mutex
private:
    MyLog(std::string logName);
    ~MyLog();
private:
    static MyLog* instance;
};

#define MyDebug(str) do \
    { \
        std::string temp; \
        temp += __FILE__; \
        temp += ","; \
        temp += __FUNCTION__; \
        temp += ",line "; \
        temp += MyHelp::ToStr(__LINE__,10); \
        temp += ": "; \
        temp += str; \
        my_master::MyLog::GetInstance()->AddLog(temp); \
    }while(0)

} // end namespace
#endif // MyLog_h__