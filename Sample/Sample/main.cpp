#include "../../MyHelp.h"
#include "../../MyWin32Help.h"
#include "../../MyHid.h"
#include "../../MyLog.h"
#include <iostream>

int main()
{
	std::cout << MyWin32Help::GetCurTime() << std::endl;
	MyLog log("mylog.txt");
	while (true)
	{
		MyWin32Help::HiResSleep(4);
		log.AddLog("xxxxxx");
	}

	system("pause");
	return 0;
}