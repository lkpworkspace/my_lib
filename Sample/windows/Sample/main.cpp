#include "../../MyHelp.h"
#include "../../windows/MyWin32Help.h"
#include "../../MyHid.h"
#include "../../windows/MyWin32Help.h"
#include <iostream>

int main()
{
	std::cout << MyWin32Help::GetCurTime() << std::endl;
	
	LARGE_INTEGER begin = MyWin32Help::GetCurClockCount();
	Sleep(10);
	LARGE_INTEGER end = MyWin32Help::GetCurClockCount();
	std::cout << MyWin32Help::GetInervalTime(end, begin);

	system("pause");
	return 0;
}