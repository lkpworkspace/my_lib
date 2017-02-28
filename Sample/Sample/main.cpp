#include "../../MyHelp.h"
#include "../../MyWin32Help.h"
#include "../../MyHid.h"
#include <iostream>

int main()
{
	std::cout << MyWin32Help::GetCurTime() << std::endl;

	system("pause");
	return 0;
}