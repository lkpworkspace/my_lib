#ifndef __COMMON_H__
#define __COMMON_H__
// c++ normal
#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <cstring>
// c++ stl
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
// win or linux
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
// my class
#include "MyHelp.h"
#include "MyVec.h"
#include "MyList.h"
#include "MyEvent.h"
#include "MyThread.h"

class Common
{
public:
    static bool SetNonblock(int fd, bool b);
    static int GetFileLen(const char* path);
    static bool IsFileExist(const char* path);
    static bool IsDirExist(const char* path);
    static char* GetHomeDir();
private:
    Common();
    ~Common();
};

#endif // COMMON_H
