#include "MyHelp.h"
#include <ctime>

// �ַ���ת����
int MyHelp::ToInt(const char *str)
{
	return atoi(str);
}
float MyHelp::ToFloat(const char *str)
{
	char* pEnd; // (out)ָ������ĵط�,Ҳ���ǲ����������ĵط�(�������ո�tab��)
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

// ����ת�ַ���
std::string MyHelp::ToStr(int num, int base)
{// num Ϊ 10���Ƶ���
	char buf[20] = { 0 };
	itoa(num, buf, base);
	return std::string(buf);
}
std::string MyHelp::ToStr(long num, int base)
{// num Ϊ 10���Ƶ���
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
// �ָ��ַ���
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
// ��ȡ��ǰʱ��
std::string MyHelp::GetCurTime()
{
	time_t now_time;
	char tmp[64] = { 0 };

	now_time = time(NULL);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&now_time));
	return std::string(tmp);
}
//size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
//���ݸ�ʽ�ַ��������ַ�����
//struct tm *localtime(const time_t *timer);
//ȡ�õ���ʱ�䣬localtime��ȡ�Ľ���ɽṹtm����
//���ص��ַ������������еĸ�ʽ������
//%a ���ڼ�����д��Eg : Tue
//%A ���ڼ���ȫ���� Eg : Tuesday
//%b �·����Ƶ���д��
//%B �·����Ƶ�ȫ����
//%c ���ض�����ʱ��ϼѱ�ʾ�ַ�����
//%d �����ֱ�ʾ���µĵڼ���(��ΧΪ 00 �� 31)������
//%H �� 24 Сʱ�����ֱ�ʾСʱ��(��ΧΪ 00 �� 23)��
//%I �� 12 Сʱ�����ֱ�ʾСʱ��(��ΧΪ 01 �� 12)��
//%j �����ֱ�ʾ����ȵĵڼ���(��ΧΪ 001 �� 366)��
//%m �·ݵ�����(��Χ�� 1 �� 12)��
//%M ���ӡ�
//%p �� ''AM'' �� ''PM'' ��ʾ���ض�ʱ�䡣
//%S ������
//%U ���ֱ�ʾΪ����ȵĵڼ��ܣ���һ�������ɵ�һ�����տ�ʼ��
//%W ���ֱ�ʾΪ����ȵĵڼ��ܣ���һ�������ɵ�һ����һ��ʼ��
//%w �����ֱ�ʾ���ܵĵڼ���(0 Ϊ����)��
//%x ����ʱ������ڱ�ʾ����
//%X �������ڵ�ʱ���ʾ���� Eg : 15 : 26 : 30
//% y ��λ���ֱ�ʾ���(��Χ�� 00 �� 99)��
//%Y ������������ֱ�ʾ������λ���� Eg : 2008
//% Z(%z) ʱ����������д��Eg : �й���׼ʱ��
//%% % �ַ���




