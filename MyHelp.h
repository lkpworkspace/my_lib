#ifndef __MyHelp_H__
#define __MyHelp_H__
#include <cstdlib>
#include <string>
#include <vector>

class MyHelp
{
public:
	// �ַ���ת����
	static int ToInt(const char *str);
	static float ToFloat(const char *str);
	static double ToDouble(const char* str);
	static long double ToLDouble(const char* str);
	static long ToLong(const char* str, int base);
	static long long ToLLong(const char* str, int base);
	static unsigned long ToULong(const char* str, int base);
	static unsigned long long ToULLong(const char* str, int base);
	// ����ת�ַ���
	static std::string ToStr(int num, int base);
	static std::string ToStr(long num, int base);
	static std::string ToStr(unsigned long num, int base);
	// �ָ��ַ���
	static std::vector<std::string> SplitStr(std::string str, char split);
	// ��õ�ǰʱ��
	static std::string GetCurTime();
};
#endif