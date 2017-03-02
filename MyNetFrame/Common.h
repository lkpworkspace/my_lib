#ifndef __COMMON_H__
#define __COMMON_H__
// c++ normal
#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>
#include <string>
#include <cstdlib>
// c++ stl
#include <list>
#include <vector>
#include <queue>
#include <map>
// win or linux
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Common
{
public:
    Common();
    ~Common();
};

#endif // COMMON_H
