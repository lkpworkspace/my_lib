#include "MyHelp.h"
#include <ctime>

// 字符串转数字
int MyHelp::ToInt(const char *str)
{
	return atoi(str);
}
float MyHelp::ToFloat(const char *str)
{
	char* pEnd; // (out)指向结束的地方,也就是不符合条件的地方(不包含空格，tab键)
	return strtof(str,&pEnd);
}
double MyHelp::ToDouble(const char* str)
{
	char* pEnd;
	return strtod(str,&pEnd);
}
long double MyHelp::ToLDouble(const char* str)
{
	char* pEnd;
	return strtold(str, &pEnd);
}
long MyHelp::ToLong(const char* str, int base)
{
	char* pEnd;
	return strtol(str, &pEnd, base);
}
long long MyHelp::ToLLong(const char* str, int base)
{
	char* pEnd;
	return strtoll(str, &pEnd, base);
}
unsigned long MyHelp::ToULong(const char* str, int base)
{
	char* pEnd;
	return strtoul(str, &pEnd, base);
}
unsigned long long MyHelp::ToULLong(const char* str, int base)
{
	char* pEnd;
	return strtoull(str, &pEnd, base);
}

// 数字转字符串
std::string MyHelp::ToStr(int num, int base)
{// num 为 10进制的数
	char buf[20] = { 0 };
	itoa(num, buf, base);
	return std::string(buf);
}
std::string MyHelp::ToStr(long num, int base)
{// num 为 10进制的数
	char buf[20] = { 0 };
	ltoa(num, buf, base);
	return std::string(buf);
}
std::string MyHelp::ToStr(unsigned long num, int base)
{
	char buf[20] = { 0 };
	ultoa(num, buf, base);
	return std::string(buf);
}
// 分割字符串
std::vector<std::string> MyHelp::SplitStr(std::string str, char split)
{
	int pos;
	std::vector<std::string> res;
	str += split;
	int size = str.size();

	for (int i = 0; i < size; ++i)
	{
		pos = str.find(split, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			res.push_back(s);
			i = pos;
		}
	}
	return res;
}
// 获取当前时间
std::string MyHelp::GetCurTime()
{
	time_t now_time;
	char tmp[64] = { 0 };

	now_time = time(NULL);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&now_time));
	return std::string(tmp);
}
//size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
//根据格式字符串生成字符串。
//struct tm *localtime(const time_t *timer);
//取得当地时间，localtime获取的结果由结构tm返回
//返回的字符串可以依下列的格式而定：
//%a 星期几的缩写。Eg : Tue
//%A 星期几的全名。 Eg : Tuesday
//%b 月份名称的缩写。
//%B 月份名称的全名。
//%c 本地端日期时间较佳表示字符串。
//%d 用数字表示本月的第几天(范围为 00 至 31)。日期
//%H 用 24 小时制数字表示小时数(范围为 00 至 23)。
//%I 用 12 小时制数字表示小时数(范围为 01 至 12)。
//%j 以数字表示当年度的第几天(范围为 001 至 366)。
//%m 月份的数字(范围由 1 至 12)。
//%M 分钟。
//%p 以 ''AM'' 或 ''PM'' 表示本地端时间。
//%S 秒数。
//%U 数字表示为本年度的第几周，第一个星期由第一个周日开始。
//%W 数字表示为本年度的第几周，第一个星期由第一个周一开始。
//%w 用数字表示本周的第几天(0 为周日)。
//%x 不含时间的日期表示法。
//%X 不含日期的时间表示法。 Eg : 15 : 26 : 30
//% y 二位数字表示年份(范围由 00 至 99)。
//%Y 完整的年份数字表示，即四位数。 Eg : 2008
//% Z(%z) 时区或名称缩写。Eg : 中国标准时间
//%% % 字符。




